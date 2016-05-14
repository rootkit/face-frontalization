// #pragma once
#ifndef CHECK_RESOURCES_H
#define CHECK_RESOURCES_H

#include <string>
#include <stdio.h>
#include <curl/curl.h>
// #include <bzlib.h>


int progress_bar (void* ptr, double TotalToDownload, double NowDownloaded, \
                    double TotalToUpload, double NowUploaded) {
    printf("%f : %f \n", TotalToDownload, NowDownloaded);
    return 0;
}

void download_file () {
    CURL *curl;
    CURLcode res;
    char outFileName[FILENAME_MAX] = "shape_predictor_68_face_landmarks.dat.bz2";
    std::string url = "http://ufpr.dl.sourceforge.net/project/dclib/dlib/v18.10/shape_predictor_68_face_landmarks.dat.bz2";
    FILE *fp;


    printf("%s%s\n", "[#] Downloading: ", outFileName);

    curl = curl_easy_init ();
    if (curl) {
        fp = fopen (outFileName, "wb");

        curl_easy_setopt (curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        // Internal CURL progressmeter must be disabled if we provide our own callback
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
        // Install the callback function
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_bar);

        res = curl_easy_perform (curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "%s%s\n", "curl_easy_perform() failed : ", curl_easy_strerror(res));
        }

        curl_easy_cleanup (curl);
        fclose (fp);
    }
}

void extract_bz2 () {

}


void check_dlib_landmark_weights (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
    } else {
        download_file ();
    }
}


#endif  // CHECK_RESOURCES_H
