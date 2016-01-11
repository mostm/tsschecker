//
//  main.c
//  tsschecker
//
//  Created by tihmstar on 22.12.15.
//  Copyright © 2015 tihmstar. All rights reserved.
//

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "download.h"
#include "ipswme.h"

#define FLAG_LIST_IOS       1 << 0
#define FLAG_LIST_DEVIECS   1 << 1
#define FLAG_OTA            1 << 2

static struct option longopts[] = {
    { "list-devices",   no_argument,       NULL, 'l' },
    { "list-ios",       no_argument,       NULL, 'l' },
    { "device",         required_argument, NULL, 'd' },
    { "ios",            required_argument, NULL, 'i' },
    { "help",           no_argument,       NULL, 'h' },
    { "baseband",       no_argument,       NULL, 'b' },
    
    { "cydia",   no_argument,       NULL, 's' },
    { "exclude", no_argument,       NULL, 'x' },
    { "shsh",    no_argument,       NULL, 't' },
    { "pwn",     no_argument,       NULL, 'p' },
    { "no-action", no_argument,     NULL, 'n' },
    { "cache-path", required_argument, NULL, 'C' },
    { NULL, 0, NULL, 0 }
};

void cmd_help(){
    printf("Usage: tsschecker [OPTIONS]\n");
    printf("Checks (real) signing status of device/firmware\n\n");
    
    printf("  -d, --device MODEL\tspecific device by its MODEL (eg. iPhone4,1)\n");
    printf("  -i, --ios VERSION\tspecific iOS version (eg. 6.1.3)\n");
    printf("  -h, --help\t\tprints usage information\n");
    printf("  -o, --ota\t\tcheck OTA signing status, instead of normal restore\n");
    printf("  -b, --baseband\t\tcheck baseband signing status, instead of normal restore\n");
    printf("      --list-devices\t\tlist all known devices\n");
    printf("      --list-ios\t\tlist all known ios versions\n");
    printf("  -a, --add\t\tadd connected devices to list of know devices\n");
    printf("           \t\tthese devices' ECID will be used to check tss status instead of random values\n");
    printf("           \t\tshsh blobs are saved for these devices in case the version is signed\n");
    printf("\n");
}

void cmd_list_devices(){
    
}

void cmd_list_ios(){
    
}


int main(int argc, const char * argv[]) {
    
    int optindex = 0;
    int opt = 0;
    long flags = 0;
    
    
    char *device = 0;
    char *ios = 0;
    
//    if (argc == 1){
//        cmd_help();
//        return -1;
//    }
//    while ((opt = getopt_long(argc, (char* const *)argv, "hd:i:l", longopts, &optindex)) > 0) {
//        switch (opt) {
//            case 'h':
//                cmd_help();
//                return 0;
//            case 'd':
//                device = optarg;
//                break;
//            case 'i':
//                ios = optarg;
//                break;
//            case 'o':
//                flags |= FLAG_OTA;
//                break;
//            case 'l':
//                for (int i=0; longopts[i].name != NULL; i++) {
//                    if (strncmp(longopts[i].name, argv[optindex-1], strlen(longopts[i].name)) == 0) {
//                        flags |= (i == 0) ? FLAG_LIST_DEVIECS : FLAG_LIST_IOS;
//                        break;
//                    }
//                }
//                break;
//            default:
//                cmd_help();
//                return -1;
//        }
//    }
    
    printf("device=%s\nios=%s\n",device,ios);
    downloadFile("https://api.ipsw.me/v2.1/firmwares.json", "/tmp/firmware.json");
    
    FILE *f = fopen("/tmp/firmware.json", "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char *firmwareJson = malloc(fsize + 1);
    fread(firmwareJson, fsize, 1, f);
    fclose(f);
    
    char *list;
    size_t cnt;
    getListOfDevices(firmwareJson, &list, &cnt);
    
    
    //list of all devices http://itunes.apple.com/check/version
    
    //api https://api.ipsw.me/docs/2.1/
    //api https://api.ipsw.me/v2.1/firmwares.json
    
    printf("done\n");
    return 0;
}