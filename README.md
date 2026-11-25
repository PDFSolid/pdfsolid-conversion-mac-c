# PDFSolid Conversion SDK for C (macOS)

High-performance C SDK for converting PDF to Word, Excel, PowerPoint, HTML, Image, TXT, RTF, CSV, JSON, Markdown, Searchable PDF, and OFD with AI-powered OCR, layout analysis, and table recognition. SDK v1.3.0 also converts Word documents (`.docx`) to PDF.

## Features

- **PDF to Word** (.docx) — Flow and Box layout modes
- **Word to PDF** (.docx → .pdf) — optional page ranges and PDF bookmarks
- **PDF to Excel** (.xlsx) — per-table, per-page, or per-document worksheet options
- **PDF to PowerPoint** (.pptx)
- **PDF to HTML** (.html) — single/multi-page with optional bookmark navigation
- **PDF to CSV** (.csv)
- **PDF to Image** (.png, .jpg, .jpeg, .jpeg2000, .bmp, .tiff, .tga, .gif, .webp) — color/grayscale/binary, configurable scaling
- **Image to Image** — supported image inputs, including individual frames of multi-page TIFF files
- **PDF to Plain Text** (.txt) — optional table format preservation
- **PDF to RTF** (.rtf)
- **PDF to Searchable PDF** (.pdf) — OCR with transparent text layer
- **PDF to OFD** (.ofd) — OCR, page background preservation, transparent text layer
- **PDF to JSON** (.json) — structured data with table extraction
- **PDF to Markdown** (.md)

### AI-Powered Document Tools

- **OCR** — Optical Character Recognition for scanned documents and images
- **Layout Analysis** — AI-based document structure parsing
- **Table Recognition** — AI-based table structure reconstruction
- **Custom AI Models** — plug in your own OCR, layout, or table engine via callbacks (SDK v1.1.0+)

## Requirements

| Platform | System Requirements | Development Environment |
| -------- | ------------------- | ----------------------- |
| macOS | macOS 11.0+ (Intel x86_64, Apple Silicon arm64) | Xcode 13.0+ |

## Quick Start

### 1. Get a License

Contact [sales@pdfsolid.com](mailto:sales@pdfsolid.com) for a 30-day free trial or commercial license.

### 2. Apply License and Initialize

```c
#include "pdfsolid_common_c.h"

CSDKErrorCode code = CPDF_LicenseVerify("LICENSE_KEY", "device_id", "app_id");
if (code != e_CErrSuccess) {
    return code;
}

CPDF_Initialize("PDFSolid_Conversion_SDK/resource");
```

### 3. Convert

```c
#include "pdfsolid_conversion_c.h"

CConvertOption option = CPDF_CONVERT_OPTION_DEFAULT;
CPDF_StartPDFToWord("input.pdf", "", "output.docx", option, NULL);
```

### Release Resources

```c
CPDF_Release();
```

## Conversion Examples

### Word (DOCX) to PDF

After applying the license and initializing the SDK, pass the input `.docx` path and a writable output `.pdf` path.

```c
#include <stddef.h>
#include "pdfsolid_conversion_c.h"

CConvertOption word_options = CPDF_CONVERT_OPTION_DEFAULT;
CSDKErrorCode result = CPDF_StartWordToPDF("input.docx", "output.pdf", word_options, NULL, NULL);
```

The default converts all pages without PDF bookmarks. Set `word_options.page_ranges` to select pages (for example, `1-2`) and `word_options.word_pdf_bookmark_mode` to generate bookmarks from headings or Word bookmarks. Check the returned status before using the PDF. `e_CErrUnsupportedFeature` means the input contains features that may affect fidelity; a PDF may still have been written.

To collect diagnostics, pass a caller-owned `char` buffer of `CPDF_WORD_TO_PDF_DIAGNOSTICS_SIZE` bytes as the last argument. See the [public header](include/pdfsolid_conversion_c.h) and [C sample](samples/demo/demo.c).

### PDF to Excel

```c
CConvertOption option = CPDF_CONVERT_OPTION_DEFAULT;
option.excel_worksheet_option = e_CForTable;
CPDF_StartPDFToExcel("input.pdf", "", "output.xlsx", option, NULL);
```

### PDF to Image

```c
CConvertOption option = CPDF_CONVERT_OPTION_DEFAULT;
option.image_type = e_CPNG;
option.image_scaling = 2.0f;
CPDF_StartPDFToImage("input.pdf", "", "output", option, NULL);
```

### PDF to Searchable PDF (OCR)

```c
CPDF_SetDocumentAIModel("path/model");

CConvertOption option = CPDF_CONVERT_OPTION_DEFAULT;
option.enable_ocr = true;
COCRLanguage languages[] = { e_CENGLISH };
option.languages = languages;
option.language_count = 1;
option.transparent_text = true;
CPDF_StartPDFToSearchablePDF("scan.pdf", "", "output.pdf", option, NULL);
```

### PDF to JSON with Table Extraction

```c
CConvertOption option = CPDF_CONVERT_OPTION_DEFAULT;
option.json_contain_table = true;
CPDF_StartPDFToJson("input.pdf", "", "output.json", option, NULL);
```

### Custom AI Engine (SDK v1.1.0+)

```c
static bool my_ocr(const char *image_path) { /* your OCR */ return true; }
static const char *my_ocr_result(void) { return ""; }
static bool my_layout(const char *image_path) { /* your layout */ return true; }
static const char *my_layout_result(void) { return ""; }
static bool my_table(const char *image_path) { /* your table */ return true; }
static const char *my_table_result(void) { return ""; }

CConvertCallback callback = {0};
callback.ocr = my_ocr;
callback.get_ocr_result = my_ocr_result;
callback.layout = my_layout;
callback.get_layout_result = my_layout_result;
callback.table = my_table;
callback.get_table_result = my_table_result;

CConvertOption option = CPDF_CONVERT_OPTION_DEFAULT;
option.enable_ocr = true;
option.enable_ai_layout = true;
CPDF_StartPDFToWord("input.pdf", "", "output.docx", option, &callback);
```

## Documentation

- [Developer Guide](doc/developer_guide_c.md)
- [API Reference](doc/api_reference_c.html)

## Contact

- Website: [https://www.pdfsolid.com](https://www.pdfsolid.com/)
- Sales: [sales@pdfsolid.com](mailto:sales@pdfsolid.com)
- Support: [support@pdfsolid.com](mailto:support@pdfsolid.com)
