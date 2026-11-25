#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "pdfsolid_common_c.h"
#include "pdfsolid_conversion_c.h"

// Paths are relative to samples/demo/build/, where RunDemo.sh executes ./demo.
static const char* DEFAULT_LICENSE = "../../../resource/license/license.xml";
static const char* PASSWORD = "";

static void progress_callback(int current_page_count, int total_page_count)
{
    printf("convert rate: %d/%d\n", current_page_count, total_page_count);
}

static bool cancel_callback(void)
{
    return false;
}

static void print_result(const char* name, CSDKErrorCode error_code)
{
    printf("%s: %d\n", name, (int)error_code);
}

static int run_word_to_pdf(CConvertCallback* callback)
{
    CConvertOption word_options = CPDF_CONVERT_OPTION_DEFAULT;
    char diagnostics[CPDF_WORD_TO_PDF_DIAGNOSTICS_SIZE] = { 0 };
    CSDKErrorCode err1 = CPDF_StartWordToPDF("../../input_files/word.docx",
                                             "../../output_files/word_to_pdf.pdf",
                                             word_options, callback, NULL);
    print_result("word to pdf", err1);

    word_options.word_pdf_bookmark_mode = e_CWordPdfBookmarkHeadings;
    snprintf(word_options.page_ranges, sizeof(word_options.page_ranges), "%s", "1-2");
    CSDKErrorCode err2 = CPDF_StartWordToPDF("../../input_files/word.docx",
                                             "../../output_files/word_to_pdf_bookmarks.pdf",
                                             word_options, callback, diagnostics);
    print_result("word to pdf with options", err2);
    if (diagnostics[0] != '\0') {
        printf("word to pdf diagnostics:\n%s\n", diagnostics);
    }
    return (err1 == e_CErrSuccess && (err2 == e_CErrSuccess || err2 == e_CErrUnsupportedFeature)) ? 0 : 1;
}

int main(int argc, char** argv)
{
    const char* license = (argc > 1 && argv[1][0] != '\0') ? argv[1] : DEFAULT_LICENSE;
    CConvertOption options = CPDF_CONVERT_OPTION_DEFAULT;
    CConvertCallback callback;
    COCRLanguage languages[] = { e_CENGLISH };
    char version[64] = { 0 };

    memset(&callback, 0, sizeof(callback));
    callback.progress = progress_callback;
    callback.cancel = cancel_callback;

    CPDF_GetVersion(version);
    printf("pdfsolid conversion sdk version: %s\n", version);

    CSDKErrorCode lic_err = CPDF_LicenseVerify(license, "", "");
    print_result("pdfsolid conversion sdk license verify", lic_err);
    if (lic_err != e_CErrSuccess) {
        return 3;
    }

    CPDF_Initialize("../../../resource");
    CPDF_SetLogger(false, false);

    CSDKErrorCode model_err = CPDF_SetDocumentAIModel("../../../resource/models/documentai.model", -1);
    print_result("set document ai model", model_err);
    if (model_err != e_CErrSuccess) {
        CPDF_Release();
        return 4;
    }

    int failures = 0;
    CSDKErrorCode err;
    err = CPDF_StartPDFToWord("../../input_files/word.pdf", PASSWORD, "../../output_files/word.docx", options, &callback);
    print_result("pdf to word", err); if (err != e_CErrSuccess) failures++;
    err = CPDF_StartPDFToExcel("../../input_files/excel.pdf", PASSWORD, "../../output_files/excel.xlsx", options, &callback);
    print_result("pdf to excel", err); if (err != e_CErrSuccess) failures++;
    err = CPDF_StartPDFToPpt("../../input_files/powerpoint.pdf", PASSWORD, "../../output_files/powerpoint.pptx", options, &callback);
    print_result("pdf to ppt", err); if (err != e_CErrSuccess) failures++;

    options.excel_csv_format = true;
    err = CPDF_StartPDFToExcel("../../input_files/excel.pdf", PASSWORD, "../../output_files/", options, &callback);
    print_result("pdf to csv", err); if (err != e_CErrSuccess) failures++;
    options.excel_csv_format = false;

    options.page_layout_mode = e_PageLayoutModeBox;
    err = CPDF_StartPDFToHtml("../../input_files/word.pdf", PASSWORD, "../../output_files/html.html", options, &callback);
    print_result("pdf to html", err); if (err != e_CErrSuccess) failures++;
    err = CPDF_StartPDFToRtf("../../input_files/word.pdf", PASSWORD, "../../output_files/rtf.rtf", options, &callback);
    print_result("pdf to rtf", err); if (err != e_CErrSuccess) failures++;
    err = CPDF_StartPDFToImage("../../input_files/word.pdf", PASSWORD, "../../output_files/", options, &callback);
    print_result("pdf to image", err); if (err != e_CErrSuccess) failures++;
    err = CPDF_StartPDFToTxt("../../input_files/word.pdf", PASSWORD, "../../output_files/txt.txt", options, &callback);
    print_result("pdf to txt", err); if (err != e_CErrSuccess) failures++;
    err = CPDF_StartPDFToJson("../../input_files/word.pdf", PASSWORD, "../../output_files/json.json", options, &callback);
    print_result("pdf to json", err); if (err != e_CErrSuccess) failures++;
    err = CPDF_StartPDFToMarkdown("../../input_files/word.pdf", PASSWORD, "../../output_files/markdown.md", options, &callback);
    print_result("pdf to markdown", err); if (err != e_CErrSuccess) failures++;

    options.enable_ocr = true;
    options.transparent_text = true;
    options.languages = languages;
    options.language_count = 1;
    err = CPDF_StartPDFToSearchablePDF("../../input_files/word.pdf", PASSWORD, "../../output_files/pdf.pdf", options, &callback);
    print_result("pdf to searchable pdf", err); if (err != e_CErrSuccess) failures++;
    err = CPDF_StartPDFToOfd("../../input_files/word.pdf", PASSWORD, "../../output_files/pdf.ofd", options, &callback);
    print_result("pdf to ofd", err); if (err != e_CErrSuccess) failures++;

    failures += run_word_to_pdf(&callback);

    CPDF_ReleaseDocumentAIModel();
    CPDF_Release();
    return failures == 0 ? 0 : 5;
}
