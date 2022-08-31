
#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include "Includes/base64.hpp"
#include "KittyMemory/MemoryPatch.h"
#include "Includes/Logger.h"
#include "Includes/Utils.h"
#include "Includes/obfuscate.h"

#include "Menu/Sounds.h"
#include "Menu/Menu.h"

#include "Toast.h"

#if defined(__aarch64__) //Compile for arm64 lib only
#include <And64InlineHook/And64InlineHook.hpp>
#else //Compile for armv7 lib only. Do not worry about greyed out highlighting code, it still works

#include <Substrate/SubstrateHook.h>
#include <Substrate/CydiaSubstrate.h>

#endif

// estrutura sofisticada para patches para kittyMemory
struct Variaveis {
    // vamos supor que temos patches para essas funções para qualquer jogo
    // like show in miniMap boolean function
    MemoryPatch ZePedrinha;
    // etc...
} hexPatches;

bool feature2 = false;
// Ponteiro de função dividido porque queremos evitar travamento quando a lib il2cpp não está carregada.
// Se você colocou getAbsoluteAddress aqui, a lib tenta ler o endereço sem il2cpp carregado,
// resultará em um ponteiro nulo que causará falha

//Target lib here
#define libil2cpp OBFUSCATE("libil2cpp.so")
#define libunity OBFUSCATE("libunity.so")
extern "C" {
JNIEXPORT void JNICALL
Java_curso_udemy_modmenu_Preferences_Changes(JNIEnv *env, jclass clazz, jobject obj,
                                        jint feature, jint value, jboolean boolean, jstring str) {

    const char *featureName = env->GetStringUTFChars(str, 0);
    feature += 1;  // No need to count from 0 anymore. yaaay :)))

    LOGD(OBFUSCATE("Feature name: %d - %s | Value: = %d | Bool: = %d"), feature, featureName, value,
         boolean);

    //!!! BE CAREFUL NOT TO ACCIDENTLY REMOVE break; !!!//

    switch (feature) {
        case 1:
            // NÃO E USADO
            break;
        case 2:
            // NÃO E USADO
            break;
        case 3:
            feature2 = boolean;
            if (feature2) {
                hexPatches.ZePedrinha.Modify();
                LOGD("LIGADO");
            } else {
                hexPatches.ZePedrinha.Restore();
                LOGD("DESLIGADO");
            }
            break;
}
}

// ---------- Hooking ---------- //
static void *gameManager = nullptr;
void (*old_LateUpdate)(void*);
void my_LateUpdate(void *_this)
{
    if (_this)
    {
        gameManager = _this;

        old_LateUpdate(gameManager);
    }

}

void *hack_thread(void *) {
    LOGI(OBFUSCATE("pthread called"));

    //Check if target lib is loaded
    do {
        sleep(1);
    } while (!isLibraryLoaded(libil2cpp));

    do {

    sleep(1);
} while (!isLibraryLoaded(libunity));

    LOGI(OBFUSCATE("%s has been loaded"), (const char *) libunity);
    LOGI(OBFUSCATE("%s has been loaded"), (const char *) libil2cpp);

#if defined(__aarch64__) //Compile for arm64 lib only


#else //Compile for armv7 lib only. Do not worry about greyed out highlighting code, it still works

    hexPatches.ZePedrinha = MemoryPatch(libil2cpp, 0xEF2B60, "\xC9\x3C\x8E\xBF\xC9\x3C\x8E\xBF\xC9\x3C\x8E\xBF\xC9\x3C\x8E\xBF", 16);




    MSHookFunction((void *) getAbsoluteAddress(libil2cpp,0x305640),(void *)my_LateUpdate,(void ** )& old_LateUpdate);

    LOGI(OBFUSCATE("Hooked"));
#endif

    return NULL;
}

//No need to use JNI_OnLoad, since we don't use JNIEnv
//We do this to hide OnLoad from disassembler
__attribute__((constructor))
void lib_main() {
    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}

/*
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *globalEnv;
    vm->GetEnv((void **) &globalEnv, JNI_VERSION_1_6);

    return JNI_VERSION_1_6;
}
 */
}