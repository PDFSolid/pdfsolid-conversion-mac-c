#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "pdfsolid_common_c.h"
#include "pdfsolid_conversion_c.h"

static const char* LICENSE = "../../../resource/license/license.xml";
static const char* PASSWORD = "";
static int failed_conversions = 0;

static void progress_callback(int current_page_count, int total_page_count)
{
    printf("convert rate: %d/%d\n", current_page_count, total_page_count);
}

static bool cancel_callback()
{
    return false;
}

static void print_result(const char* name, CSDKErrorCode error_code)
{
    printf("%s: %d\n", name, (int)error_code);
    if ((int)error_code != 0) ++failed_conversions;
}

int main(void)
{
    CConvertOption options = CPDF_CONVERT_OPTION_DEFAULT;
    CConvertCallback callback;
    COCRLanguage languages[] = { e_CENGLISH };
    char version[30] = { 0 };

    memset(&callback, 0, sizeof(callback));
    callback.progress = progress_callback;
    callback.cancel = cancel_callback;
    callback.ocr = NULL;
    callback.get_ocr_result = NULL;
    callback.layout = NULL;
    callback.get_layout_result = NULL;
    callback.table = NULL;
    callback.get_table_result = NULL;


    CSDKErrorCode license_code = CPDF_LicenseVerify(LICENSE, "", "");
    print_result("license_return_code", license_code);
    if ((int)license_code != 0) { CPDF_Release(); return 3; }
    CPDF_Initialize("../../../resource");
    CPDF_SetLogger(false, false);
    CSDKErrorCode model_code = CPDF_SetDocumentAIModel("../../../resource/models/documentai.model", -1);
    print_result("model_return_code", model_code);
    if ((int)model_code != 0) { CPDF_Release(); return 4; }

    print_result("pdf to word",
                 CPDF_StartPDFToWord("../../input_files/word.pdf", PASSWORD,
                                     "../../output_files/word.docx", options, &callback));
    print_result("pdf to excel",
                 CPDF_StartPDFToExcel("../../input_files/excel.pdf", PASSWORD,
                                      "../../output_files/excel.xlsx", options, &callback));
    print_result("pdf to ppt",
                 CPDF_StartPDFToPpt("../../input_files/powerpoint.pdf", PASSWORD,
                                    "../../output_files/powerpoint.pptx", options, &callback));

    options.excel_csv_format = true;
    print_result("pdf to csv",
                 CPDF_StartPDFToExcel("../../input_files/excel.pdf", PASSWORD,
                                      "../../output_files/", options, &callback));
    options.excel_csv_format = false;

    options.page_layout_mode = e_PageLayoutModeBox;
    print_result("pdf to html",
                 CPDF_StartPDFToHtml("../../input_files/word.pdf", PASSWORD,
                                     "../../output_files/html.html", options, &callback));
    print_result("pdf to rtf",
                 CPDF_StartPDFToRtf("../../input_files/word.pdf", PASSWORD,
                                    "../../output_files/rtf.rtf", options, &callback));
    print_result("pdf to image",
                 CPDF_StartPDFToImage("../../input_files/word.pdf", PASSWORD,
                                      "../../output_files/", options, &callback));
    print_result("pdf to txt",
                 CPDF_StartPDFToTxt("../../input_files/word.pdf", PASSWORD,
                                    "../../output_files/txt.txt", options, &callback));
    print_result("pdf to json",
                 CPDF_StartPDFToJson("../../input_files/word.pdf", PASSWORD,
                                     "../../output_files/json.json", options, &callback));
    print_result("pdf to markdown",
                 CPDF_StartPDFToMarkdown("../../input_files/word.pdf", PASSWORD,
                                         "../../output_files/markdown.md", options, &callback));

    options.enable_ocr = true;
    options.transparent_text = true;
    options.languages = languages;
    options.language_count = 1;
    print_result("pdf to searchable pdf",
                 CPDF_StartPDFToSearchablePDF("../../input_files/word.pdf", PASSWORD,
                                              "../../output_files/pdf.pdf", options, &callback));

    print_result("pdf to ofd",
                 CPDF_StartPDFToOfd("../../input_files/word.pdf", PASSWORD,
                                    "../../output_files/pdf.ofd", options, &callback));

    CPDF_GetVersion(version);
    printf("pdfsolid conversion sdk version: %s\n", version);

    CPDF_Release();
    return failed_conversions == 0 ? 0 : 5;
}
