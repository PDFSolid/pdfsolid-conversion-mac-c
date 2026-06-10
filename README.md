# PDFSolid Conversion SDK for C

A high-performance C library for extracting and transforming PDF content — text, images, tables, links, and annotations — into various file formats while preserving the original document layout.

## Supported Conversions

| Target Format | API | Extension |
| --- | --- | --- |
| Word | `CPDF_StartPDFToWord` | `.docx` |
| Excel | `CPDF_StartPDFToExcel` | `.xlsx` |
| PowerPoint | `CPDF_StartPDFToPpt` | `.pptx` |
| HTML | `CPDF_StartPDFToHtml` | `.html` |
| CSV | `CPDF_StartPDFToExcel` (with `excel_csv_format`) | `.csv` |
| Image | `CPDF_StartPDFToImage` | `.png` `.jpg` `.jpeg` `.jp2` `.bmp` `.tiff` `.tga` `.gif` `.webp` |
| RTF | `CPDF_StartPDFToRtf` | `.rtf` |
| TXT | `CPDF_StartPDFToTxt` | `.txt` |
| Searchable PDF | `CPDF_StartPDFToSearchablePDF` | `.pdf` |
| OFD | `CPDF_StartPDFToOfd` | `.ofd` |
| JSON | `CPDF_StartPDFToJson` | `.json` |
| Markdown | `CPDF_StartPDFToMarkdown` | `.md` |

AI-powered capabilities: **OCR**, **Layout Analysis**, and **Table Recognition**.

## System Requirements

| Platform | Requirements | Toolchain |
| --- | --- | --- |
| Windows | Windows 7/8/10/11 (x86, x64) | Visual Studio 2022+ |
| Linux | Linux x64 | GCC or Clang |
| macOS | macOS 10.14+ (Intel, Apple Silicon) | Xcode 13.0+ |

## Package Structure

```
├── doc/            # API reference and developer guide
├── include/        # C API header files
├── lib/            # Dynamic libraries (x86/x64)
├── resource/       # DocumentAI model resources
├── samples/        # Demo projects and sample code
├── legal.txt
├── release_notes.txt
└── README.md
```

## Quick Start

### 1. Verify License

```c
#include "pdfsolid_common_c.h"

CSDKErrorCode code = CPDF_LicenseVerify("LICENSE_KEY", "device_id", "app_id");
if (code != e_CErrSuccess) {
    return code;
}
```

### 2. Initialize SDK

```c
#if defined(_WIN32)
#define CPDF_TEXT(text) L##text
#else
#define CPDF_TEXT(text) text
#endif

CPDF_Initialize(CPDF_TEXT("PDFSolid_Conversion_SDK/resource"));
```

### 3. Convert PDF to Word

```c
#include "pdfsolid_common_c.h"
#include "pdfsolid_conversion_c.h"

CConvertOption option = CPDF_CONVERT_OPTION_DEFAULT;
CPDF_StartPDFToWord(CPDF_TEXT("input.pdf"), CPDF_TEXT(""), CPDF_TEXT("output.docx"), option, NULL);
```

### 4. Release Resources

```c
CPDF_Release();
```

## Header Files

| Header | Description |
| --- | --- |
| `pdfsolid_common_c.h` | License, initialization, resource release, version, and DocumentAI configuration |
| `pdfsolid_conversion_c.h` | PDF conversion APIs |
| `pdfsolid_basictypes_c.h` | Error codes, conversion options, image types, OCR languages, and other public types |

## Conversion Options

`CConvertOption` is a plain C struct. Use the default initializer macro:

```c
CConvertOption option = CPDF_CONVERT_OPTION_DEFAULT;
```

Key options:

| Option | Type | Description |
| --- | --- | --- |
| `enable_ai_layout` | `bool` | Enable AI layout analysis |
| `enable_ai_table_recognition` | `bool` | Enable AI table recognition |
| `enable_ocr` | `bool` | Enable OCR |
| `contain_image` | `bool` | Include images in output |
| `contain_annotation` | `bool` | Include annotations in output |
| `page_layout_mode` | `CPageLayoutMode` | `e_PageLayoutModeFlow` or `e_PageLayoutModeBox` |
| `image_type` | `CImageType` | Output image format (`e_CJPG`, `e_CPNG`, etc.) |
| `image_scaling` | `float` | Image scaling factor (default `4.0f`) |
| `page_ranges` | `char[256]` | Pages to convert, e.g. `"1-3,5,7-9"` |
| `excel_worksheet_option` | `CExcelWorksheetOption` | `e_CForTable` / `e_CForPage` / `e_CForDocument` |
| `html_option` | `CHtmlOption` | `e_CSinglePage` / `e_CMultiPage` / etc. |
| `ocr_option` | `COCROption` | `e_CAll` / `e_CScanPage` / etc. |
| `font_name` | `char[256]` | Preferred output font name |

## OCR Languages

```c
COCRLanguage languages[] = { e_CENGLISH };
option.enable_ocr = true;
option.languages = languages;
option.language_count = 1;
```

Supported: `e_CCHINESE`, `e_CCHINESE_TRA`, `e_CENGLISH`, `e_CKOREAN`, `e_CJAPANESE`, `e_CLATIN`, `e_CDEVANAGARI`, `e_CCYRILLIC`, `e_CARABIC`, `e_CTAMIL`, `e_CTELUGU`, `e_CKANNADA`, `e_CTHAI`, `e_CGREEK`, `e_CEslav`, `e_CAUTO`.

## Progress and Cancellation

```c
static void progress_callback(int current, int total) {
    printf("progress: %d / %d\n", current, total);
}

static bool cancel_callback(void) {
    return false;
}

CConvertCallback callback = {0};
callback.progress = progress_callback;
callback.cancel = cancel_callback;

CPDF_StartPDFToWord(CPDF_TEXT("input.pdf"), CPDF_TEXT(""), CPDF_TEXT("output.docx"), option, &callback);
```

## Error Handling

All conversion APIs return `CSDKErrorCode`. Always check the result:

| Error Code | Meaning |
| --- | --- |
| `e_CErrSuccess` | Success |
| `e_CErrFile` | File not found or cannot be opened |
| `e_CErrPDFPassword` | Invalid PDF password |
| `e_CErrPDFFormat` | Invalid or corrupted PDF |
| `e_CErrLicenseInvalid` | Invalid license |
| `e_CErrLicenseExpire` | License expired |
| `e_CErrLicenseConcurrencyExceeded` | Concurrency limit exceeded |
| `e_CErrOCRFailure` | OCR recognition failed |
| `e_CErrConverting` | A conversion task is already running |

## Running the Demo (Windows)

1. Open `samples/demo_vs2022.sln` in Visual Studio 2022.
2. Build via **Build > Build Solution**.
3. Run the generated `.exe` from `samples/bin/`.

Output files are written to `samples/output_files/`.

## Running the Demo (Linux / macOS)

```shell
cd samples
./RunDemo.sh
```

## Custom AI Models (SDK v4.1.0+)

You can replace the built-in DocumentAI model with your own OCR, layout analysis, or table recognition engine via callback hooks on `CConvertCallback`. See the [developer guide](doc/developer_guide_c.md) for JSON schema details.

## License

This is a commercial SDK. Contact [support@pdfsolid.com](mailto:support@pdfsolid.com) for a trial or commercial license.

## Support

- Website: [https://www.pdfsolid.com](https://www.pdfsolid.com)
- Email: [support@pdfsolid.com](mailto:support@pdfsolid.com)
