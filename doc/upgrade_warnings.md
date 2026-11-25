# PDFSolid Conversion SDK for C 1.3.0 Upgrade Warnings

This document contains a list of considerations that developers should be aware of when upgrading from previous versions to PDFSolid Conversion SDK for C 1.3.0. Changes in the code may be necessary to ensure compatibility with the new version for your project to compile properly.

**Upgrading to version 1.3.0 from version 1.2.0**

If you are upgrading from version 1.2.0 to version 1.3.0, please note the following changes between 1.2.0 and 1.3.0.

**Important: Recompile your project with the 1.3.0 header files.** `CPDF_StartWordToPDF` changed from 3 parameters to 5, so old calls no longer compile. The `CConvertOption` structure has new members and the `CPDF_CONVERT_OPTION_DEFAULT` macro has new initial values, so programs compiled with the old headers are no longer binary compatible with the new library and must be recompiled.

**Important: The default table recognition model profile has changed.** 1.2.0 used the high accuracy model by default; 1.3.0 uses the balanced model by default. Even if you do not change any code, the table recognition results and resource usage will differ from 1.2.0 after the upgrade. To keep the behavior of 1.2.0, select the high accuracy profile explicitly and load the table extension package `table_legacy.model` (see item 1 under "In the conversion options" below). Also note that if you zero a `CConvertOption` with `memset` or `{0}` and then assign the fields one by one, the new `table_recognition_accuracy` is 0, which is the high accuracy profile, not the 1.3.0 default (the balanced profile). To get the balanced profile, initialize with `CPDF_CONVERT_OPTION_DEFAULT` or set `table_recognition_accuracy = e_CBalanced` explicitly.

**Important: Upgrade the model files together with the SDK.** The `documentai.model` of 1.2.0 and earlier does not contain the resources required by the balanced profile, while the 1.3.0 model file keeps the same file name, so **continuing to use the old file causes model loading to fail. Overwrite the old file in your deployment directory with the `documentai.model` included in the 1.3.0 SDK package.** If you need extended features such as high accuracy tables, high accuracy OCR, or orientation correction, download the corresponding extension model packages. For the composition and purpose of the model packages, see chapter "4.2 Set DocumentAI Model" of the developer guide.

In the library management operations:

1. `CPDF_SetDocumentAIModel` now supports loading model packages incrementally. The base package `documentai.model` provides layout analysis, balanced-profile table recognition, and basic OCR; capabilities such as tables, OCR, and orientation correction are provided by extension packages. Each call loads only the capabilities contained in that file and merges them with the capabilities that are already loaded; it does not replace them. Example:

   ```c
   CPDF_SetDocumentAIModel(CPDF_TEXT("path/documentai.model"), -1);
   CPDF_SetDocumentAIModel(CPDF_TEXT("path/table_legacy.model"), -1);
   ```

   If a package fails to load, the capabilities that are already loaded are kept and the specific error code is returned.

2. The timing of release and configuration has changed. If synchronous conversion tasks are still running when `CPDF_Release` is called, the release is postponed until the last task ends, and new tasks are rejected during this period. While tasks are running or a release has not finished, setting the DocumentAI model again is rejected and `e_CErrConverting` is returned. Unload the SDK only after all conversion interfaces have returned.

3. The new `CPDF_GetLicenseType` interface returns the type of the currently verified license: `e_CLicenseUnknown`, `e_CLicenseTrial`, or `e_CLicenseFormal` (type `CLicenseType`). It does not verify the license again and does not consume page quota.

In the file conversion operations:

1. The new Word to PDF interface `CPDF_StartWordToPDF` is added. Its options share `CConvertOption` with PDF conversion; only the new `word_pdf_bookmark_mode` (bookmark mode, type `CWordPdfBookmarkMode`: `e_CWordPdfBookmarkNone` generates no bookmarks, `e_CWordPdfBookmarkHeadings` generates bookmarks from headings, `e_CWordPdfBookmarkWordBookmarks` generates bookmarks from Word bookmarks) and `page_ranges` (pages to output) take effect, and the other fields are ignored. Example:

   ```c
   CConvertOption options = CPDF_CONVERT_OPTION_DEFAULT;
   options.word_pdf_bookmark_mode = e_CWordPdfBookmarkHeadings;
   strcpy(options.page_ranges, "1-3,5,7-9");
   char diagnostics[CPDF_WORD_TO_PDF_DIAGNOSTICS_SIZE] = {0};

   CPDF_StartWordToPDF(CPDF_TEXT("input.docx"), CPDF_TEXT("output.pdf"), options, &callback, diagnostics);
   ```

   `diagnostics` is optional: the buffer is allocated by the caller and its size is `CPDF_WORD_TO_PDF_DIAGNOSTICS_SIZE` (8192) bytes. The SDK writes UTF-8 diagnostic text into it; pass `NULL` if it is not needed. When the document contains a feature that may affect fidelity, `e_CErrUnsupportedFeature` (95) is returned. The PDF is usually still produced; check the first line of the diagnostic text, `output=produced` or `output=not_produced`. If the buffer cannot hold the complete diagnostics, `e_CErrOutOfMemory` is returned.

2. The conversion behavior for image input has changed. The image conversion interface `CPDF_StartPDFToImage` accepts both PDF files and supported image files, and converting between images performs neither OCR nor layout analysis. Multi-page TIFF files are converted frame by frame: every selected frame produces one image, and `page_ranges` selects the frames. When OCR is off (the default) and an image is converted to a format that can carry images, the complete source image is output and no recognized text is generated. When an image input is converted to TXT or to Excel in CSV format and OCR is not enabled, `e_CErrUnsupportedFeature` (95) is now returned; enable OCR (`enable_ocr = true`).

In the conversion options:

1. Added the `table_recognition_accuracy` option (type `CTableRecognitionAccuracy`) to select the table recognition accuracy. **The default is `e_CBalanced` (balanced), which differs from 1.2.0, where the high accuracy profile was the default.** Selecting `e_CHighAccuracy` requires `table_legacy.model` to be loaded; if it is not loaded, the conversion still succeeds, but tables are recognized with the rule-based method instead, so the result differs from the high-accuracy result. To keep the behavior of 1.2.0, change the original:

   ```c
   CConvertOption option = CPDF_CONVERT_OPTION_DEFAULT;
   CPDF_StartPDFToWord(CPDF_TEXT("input_file"), CPDF_TEXT("password"), CPDF_TEXT("output_path.docx"), option, NULL);
   ```

   to:

   ```c
   CPDF_SetDocumentAIModel(CPDF_TEXT("path/documentai.model"), -1);
   CPDF_SetDocumentAIModel(CPDF_TEXT("path/table_legacy.model"), -1);

   CConvertOption option = CPDF_CONVERT_OPTION_DEFAULT;
   option.table_recognition_accuracy = e_CHighAccuracy;
   CPDF_StartPDFToWord(CPDF_TEXT("input_file"), CPDF_TEXT("password"), CPDF_TEXT("output_path.docx"), option, NULL);
   ```

2. Added the `enable_auto_page_size` option. When enabled, the page size of the output of image conversion is matched to the nearest standard paper size according to the image resolution; when disabled, one image pixel corresponds to one page point. It takes effect only when the input is an image file.

3. Added the `custom_page_width` and `custom_page_height` options, in points (1 point = 1/72 inch); `0` means not specified. When both are set, they specify the output page size directly and take precedence over `enable_auto_page_size`; the size is used as given, orientation included, and the image is scaled proportionally to fit inside the page without cropping. They take effect only when the input is an image file. Example:

   ```c
   CConvertOption option = CPDF_CONVERT_OPTION_DEFAULT;
   option.custom_page_width = 595.28f;   // A4
   option.custom_page_height = 841.89f;
   ```
