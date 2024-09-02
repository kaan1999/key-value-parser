#include <kv_parser.h>
#include <kv_tokenizer.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *const argv[])
{
    if(argc < 3) {
        fprintf(stderr, "Error: %s\n", strerror(EINVAL));
        return EINVAL;
    }
    const char *fileName = argv[1];
    const char *outputFileName = argv[2];
    kv_list_ptr tokenStream = kv_tokenizer_read(fileName);
    if(!tokenStream){
        perror("Error");
        return 1;
    }
    kv_list_ptr pairList = kv_parser(tokenStream);
    kv_list_destroy(tokenStream);
    if(!pairList){
        perror("Error");
        return 1;
    }

    FILE *outputFile = fopen(outputFileName, "w");

    char pairBuffer[1024] = {'\0'};
    kv_list_forEach(pairList, pairNode)
        kv_pair_ptr pair = kv_list_data(pairNode);
        char *key = kv_pair_key(pair);
        char *value = kv_pair_value(pair);
        strcpy(pairBuffer, key);
        strcat(pairBuffer, ":");
        strcat(pairBuffer, value);
        strcat(pairBuffer, ";");
        fprintf(outputFile, "%s\n", pairBuffer);
    kv_end
    fclose(outputFile);
    kv_list_destroy(pairList);
}