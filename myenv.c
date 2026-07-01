/*
 *  myenv.c : env コマンドのクローン
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#ifdef __linux__
#include "myputenv.h"
#endif

extern char** environ;

int main(int argc, char *argv[], char *envp[]) {
    //name=valueの形の引数を判定して環境変数に入れる
    for (int i = 1; i < argc; i++){
        if (strchr(argv[i], '=') != NULL){
            if(putenv(argv[i]) != 0) {
                perror("putenv");
                return 1;
            }
        } else {
            execvp(argv[i], &argv[i]);
            perror("execvp");
            return 1;
        }
    }

    for (int j = 0; environ[j] != NULL; j++) {
        printf("%s\n", environ[j]);
    }
    
    return 0;
}

/* 実行例

ここに実行例を書く
% ./myenv date                              <-----date を表示
2026年 7月 1日 水曜日 17時09分31秒 JST
 % ./myenv                                  <-----引数なしで表示
__CFBundleIdentifier=com.apple.Terminal
TMPDIR=/var/folders/y2/z5807b8d26vdjjw3b1_gj6br0000gn/T/
XPC_FLAGS=0x0
TERM=xterm-256color
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.G5NoSljCMB/Listeners
...
（省略）
...
INFOPATH=/opt/homebrew/share/info:
LANG=ja_JP.UTF-8
_=/Users/emiko/髃?専4年/僩??惼??/SysPro2/kadai09-i23emiko/./myenv
% ./myenv LC_TIME=US.UTF-8 TZ=RU date　     <------指定した環境変数
Wed Jul  1 08:10:39 UTC 2026
% ./myenv LC_TIME=ru_RU.UTF-8 date 
среда,  1 июля 2026 г. 17:20:16 (JST)
% ./myenv dat                               <------エラーチェック
execvp: No such file or directory


*/
