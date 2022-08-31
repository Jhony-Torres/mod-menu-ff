**ESTE MODELO NÃO É PARA NOVATOS/NOOBS, É APENAS PARA MODDERS E PROGRAMADORES EXPERIENTES. VOCÊ PRECISA LER,
APRENDER E ATÉ GOOGLE. ESTA NÃO É UMA CONFIGURAÇÃO SIMPLES DE INSTALAÇÃO COM UM CLIQUE. SE VOCÊ NÃO TEM O CONHECIMENTO, ESTE TUTORIAL SERÁ MUITO DIFÍCIL PARA VOCÊ**

**SE VOCÊ ESTÁ ATUALIZANDO ESTE MODELO, CLONE-O SEPARADAMENTE. NÃO FUNCIONE NO ANTIGO A MENOS QUE SAIBA O QUE ESTÁ FAZENDO!**

**Isso não abrange como modificar jogos em geral, funções de gancho, etc., que todos os outros tutoriais on-line já cobrem,
então não pergunte, pois não vou cobri-los. Os códigos no modelo simplesmente informam como usá-los**

**Para usuários móveis que não possuem um PC, leia [README-MOBILE.md]
(https://github.com/LGLTeam/Android-Mod-Menu/blob/master/README-MOBILE.md) 
how to use this project within AIDE app**

# Quick links
- [Prerequisites](#prerequisites)
- [Softwares you need](#softwares-you-need)
- [download/clone](#downloadclone)
- [Setting up Android Studio](#setting-up-android-studio)
- [Open the project](#open-the-project)
- [Files to work with and making changes](#files-to-work-with-and-making-changes)
- [Implementing the menu to the target game](#implementing-the-menu-to-the-target-game)
- [Loading lib without mod menu](#loading-lib-without-mod-menu)
- [FAQ](#faq)
- [Credits/Acknowledgements](#creditsacknowledgements)

# Introduction
Menu mod flutuante para il2cpp e outros jogos nativos do Android. KittyMemory, MSHook e And64InlineHook incluídos. Este modelo é otimizado para modders que desejam a maneira mais rápida de implementar o menu no jogo sem problemas. Os ativos são armazenados como base64 no cpp e não precisam ser armazenados na pasta de ativos.

Ele vem com ofuscação de string e offset sem usar nenhuma ferramenta externa e sem modificar o compilador. Usamos AY Ofuscator

Suporta Android 4.4.x até Android R. Suporta arquitetura ARMv7, x86 e ARM64. No entanto, o x86 está obsoleto para jogos do Unity, portanto, o x86 não é nossa prioridade

O menu Mod é baseado no modelo Octowolve/Escanor e Van. 

Preview:

![](https://i.imgur.com/42Sh72L.gif)

# Prerequisites
* **UM MODDER EXPERIENTE, NÃO UM MODDER NOVATO/INICIANTE:** Você deve ser capaz de modificar qualquer jogo em geral (não precisa ser um jogo protegido), como modificar arquivos .so, arquivos dll, arquivos smali, etc. .
* Conhecimento básico de opcodes smali dalvik e montagem ARM e ARM64 (x86 não é necessário), necessário para corrigir a memória
* Ser capaz de ligar a função em C++ (não é realmente necessário, mas recomendado se você quiser fazer modificações avançadas no futuro)
* Conhecimento básico de C++ e Java
* Conhecimento básico de como o layout do Android funciona em XML e Java. Este projeto usa apenas Java para layout, mas você aprenderá facilmente
* Tempo e paciência: Não comece a trabalhar nisso se tiver prazos ou trabalhos importantes, apenas no seu tempo livre. Leve o seu tempo para ler, aprender e se acostumar a trabalhar com este projeto.
* DIY (Faça você mesmo): Sim, você deve ser capaz de fazer as coisas sozinho. Se não pudermos ou não quisermos implementar alguns recursos, tente implementar você mesmo. Nós não somos os professores, não é nosso estilo, então não nos peça para ensinar ou dar de colher.
* Uma mente curiosa

# Softwares you need
* Android Studio 4 ou  Superior: https://developer.android.com/studio
* Apktool: [Apktool.jar](https://ibotpeaches.github.io/Apktool/) or any 3rd party tools
* APK Easy Tool. To get main activity: https://forum.xda-developers.com/android/software-hacking/tool-apk-easy-tool-v1-02-windows-gui-t3333960
* Any text editor. eu uso [Notepad++](https://notepad-plus-plus.org/downloads/)
* Any png compressão para comprimir o seu png Arquivo: https://compresspng.com/
* Any base64 codificação para codificar seu arquivo: https://www.base64encode.org/

# Download/Clone
Clique no botão que diz Código e clique em Baixar ZIP

![](https://i.imgur.com/EZnbd10.png)

Ou clone pelo Android Studio se você souber usar o Git

# Configurando o Android Studio

### 1. Installing NDK

No canto inferior direito,, click on Configure and SDK Manager

![](https://i.imgur.com/xBP1bCE.png)

Select **Android SDK**, check **NDK (Side by side)** e clique em OK. Ele vai baixar e instalar

![](https://i.imgur.com/FcAd2Px.png)

### 2. Open the project

Extraia o projeto de modelo para a pasta sem espaços. Se alguma pasta tiver espaços, causará problema

Na tela de boas-vindas, escolha **"Abrir um projeto existente do Android Studio"**

Navegue até o projeto extraído e abra-o

![](https://i.imgur.com/3etm4qX.png)

Ele indexará e o Gradle sincronizará o projeto pela primeira vez. Aguarde um pouco, levará cerca de 5 minutos dependendo do desempenho do seu computador

Se você encontrar um erro

```NDK não configurado. Faça o download com o gerenciador de SDK. A versão preferida do NDK é 'xx.x.xxxxxx'```

Clique em Arquivo e Estrutura do Projeto

![](https://i.imgur.com/EWhLe7M.png)

Selecione a versão padrão do NDK

![](https://i.imgur.com/YfmIvoN.png)

Depois de pronto, você pode começar a trabalhar!

# Arquivos para trabalhar e fazer alterações

### Java

**`MainActivity.java`**:
Você não precisa trabalhar com isso, a menos que esteja implementando algo como layout de login..

Static method `Start()` and `LoadLibOnly()` pode ser chamado do jogo `OnCreate`. `Start()` 
verifica se o dispositivo está executando o Android 6.0 ou superior e se a permissão de sobreposição foi verificada antes de iniciar o serviço de menu..

**`modmenu/Preferences.java`**: Salvando as preferências do recurso de menu e chamando as alterações via JNI

**`modmenu/FloatingModMenuService.java`**: Códigos principais do design do menu mod

Os códigos do menu mod flutuante. Você não precisa mudar muito, a menos que queira redesenhá-lo.
Os códigos são explicados nos comentários

Note: In the `run()` método manipulador dentro `initFloating()`, 
existe um código que verifica se a lib do jogo está carregada ou não antes de carregar as listas de recursos. Se você está correndo
o aplicativo como depurar e quiser testar as preferências, comente o código if-else, exceto a coisa da lista de recursos.
Caso contrário, ficaria preso sem um jogo

- `GradientDrawable`

Um código para definir o canto e o traço/borda interna. Funciona para qualquer componente de visualização
```
GradientDrawable gradientdrawable = new GradientDrawable();
gradientdrawable.setCornerRadius(20); //Set corner
gradientdrawable.setColor(Color.parseColor("#1C2A35")); //Set background color
gradientdrawable.setStroke(1, Color.parseColor("#32cb00")); //Set border
```

Defina o desenhável de gradiente para o componente de visualização

```
[nome do seu componente de visualização].setBackground(gradientdrawable);
```

- Redimensionamento da caixa de menu
Eu adicionei variáveis para que você possa achar fácil redimensionar
```
private final int MENU_WIDTH = 290;
private final int MENU_HEIGHT = 200;
```

Observação: talvez seja necessário implementar o dimensionamento automático devido
 a muitos tipos de telefone com DPIs e resoluções diferentes

- Animação Colorida: Os códigos podem ser vistos em `startAnimation()`

- Adding new view

Normalmente, a documentação de desenvolvimento do Android não explica o código em java. 
Se você ler a documentação de desenvolvimento do Android e vir um exemplo como TextView

```
TextView textView = (TextView) findViewById(R.id.textView);
textView.setFontVariationSettings("'wdth' 150");
```

Isso é para xml. Em vez disso, crie uma instância para java e adicione view ao seu Layou

```
TextView textView = new TextView(this);
textView.setFontVariationSettings("'wdth' 150");
LinearLayoutExample.addView(textView);

```

Há muitos mais. Embora não possamos explicar muito aqui, você pode usar o Google.
Search like `create a textview programmatically android`, `create a button programmatically android`
 etc for more infomation

### Cpp

- **`Menu.h`**: Menu relacionado com chamadas JNI

- `Title`: Texto grande

- `Heading`: Pequeno texto. Semi HTML é suportado. O texto irá rolar se o texto for muito long

- `Icon`: Imagem compactada codificada para base64

- `IconWebViewData`: e ícone na visualização da Web com suporte a animação GIF. URL requer permissão de internet `android.permission.INTERNET`

Examples

```From internet: (Requires android.permission.INTERNET)
return env->NewStringUTF("https://i.imgur.com/SujJ85j.gif"); 

From assets folder: (Requires android.permission.INTERNET)
return env->NewStringUTF("file:///android_asset/example.gif"); 

Base64 html:
return env->NewStringUTF("data:image/png;base64, <encoded base64 here>");

Nothing:
return NULL
```

**`Toast.h`**: Your toast

**`Main.cpp`**: Neste arquivo, você trabalhará com seus mods aqui

- `Changes`: Obtenha valores para aplicar mods. CUIDADO PARA NÃO REMOVER ACIDENTALMENTE o intervalo;
Você também pode usar a instrução if-else com comparação de strings

```
if (strcmp(featureName, "The button") == 0) { //Compare with string

} else if (strcmp(featureName, "The On/Off button") == 0) { //Compare with string

} else if (feature == 7) {

}
```
- `getFeatureList`: Mod features

Usage:

```
Category_(text)
Toggle_(feature name)
SeekBar_(feature name)_(min value)_(max value)
Spinner_(feature name)_(Items e.g. item1,item2,item3)
Button_(feature name)
ButtonLink_(feature name)_(URL/Link here)
ButtonOnOff_(feature name)
InputValue_(feature name)
CheckBox_(feature name)
RadioButton_(feature name)_(Items e.g. radio1,radio2,radio3)
RichTextView_(Text with limited HTML support)
RichWebView_(Full HTML support)
```

Examples:

```Toggle_God mode
Spinner_Weapons_AK47,9mm,Knife
Button_OnOff_God mode
```

Learn more about HTML https://www.w3schools.com/

- `hack_thread`: Aqui você adiciona seu código para hackear com KittyMemory ou Hooking.
Nós não vamos ensinar, você já deve ter aprendido

KittyMemory usage:
```MemoryPatch::createWithHex([Lib Name], [offset], "[hex. With or without spaces]");
[Struct].get_CurrBytes().Modify();
[Struct].get_CurrBytes().Restore();

[Struct].get_TargetAddress();
[Struct].get_PatchSize();
[Struct].get_CurrBytes().c_str();
```

Example: https://github.com/MJx0/KittyMemory/blob/master/Android/test/src/main.cpp

Hook usage:
ARM64:
```A64HookFunction((void *) getAbsoluteAddress([Lib Name], [offset]), (void *)[function], (void **)&[old function]);```

ARMv7/x86:
```MSHookFunction((void *) getAbsoluteAddress([Lib Name], [offset]), (void *)[function], (void **)&[old function]);```

**`Android.mk`**

O arquivo make para o compilador c++. Nesse arquivo, você pode alterar o nome da lib na linha `LOCAL_MODULE`
Quando você alterar o nome da lib, altere também em `System.loadLibrary("")` no método OnCreate em FloatingModMenuService.java
Ambos devem ter o mesmo nome

**C++ string obfuscation**

Usamos AY Obfuscator, mas o uso mudou para `OBFUSCATE("string here")` 
and `OBFUSCATE_KEY("string here", 'single letter here')`

Example
```
OBFUSCATE("Hello world")
OBFUSCATE_KEY("Hello world", 'a')
OBFUSCATE_KEY("Hello world", 'u')
```

### Others

**`proguard-rules.pro`**

Veja as regras do proguard aqui https://www.guardsquare.com/en/products/proguard/manual/usage

Both `shrinkResources` and `minifyEnabled` MUST be `true` in `build.gradle (:app)` para habilitar a ofuscação do proguard

`public static void Start` has been prevented from renaming

Add `-dontobfuscate` to disable obfuscation

**Encoding your files into base64**

Você pode usar praticamente qualquer ferramenta para codificação base64.

Usamos um site simples https://www.base64encode.org/

Role para baixo até ver `Encode files into Base64 format`. Clique ou toque na caixa para selecionar um arquivo

Click on `ENCODE` botão e clique em `CLICK OR TAP HERE` para baixar seu arquivo codificado. Agora você pode colá-lo em seu código

# Testing

Conecte seu dispositivo ao computador ou execute seu emulador.
Certifique-se de ter a depuração USB habilitada na opção de desenvolvedor do seu dispositivo.
O Android Studio detectará e você poderá clicar em Reproduzir para executar seu aplicativo.

![](https://i.imgur.com/ZegjeM8.png)

Às vezes, emuladores como NOX ou MEMU não conseguem se conectar ao adb automaticamente, para conectá-los, basta reiniciar o emulador.

No Android 4.2 e superior, a tela de opções do desenvolvedor fica oculta por padrão.
Para torná-lo visível, vá para **Settings** > **About phone** e toque em Número de compilação sete vezes.
Retorne à tela anterior para encontrar as opções do desenvolvedor na parte inferior.

Em alguns dispositivos, a tela de opções do desenvolvedor pode estar localizada ou nomeada de forma diferente.

# Implementando o menu para o jogo alvo

### 1. Conheça a atividade principal do seu jogo

Agora estamos procurando a atividade principal, existem 2 maneiras de fazer

1. Decompile the game's APK file. Open `androidmanifest.xml` 
e procure depois `<action android:name="android.intent.action.MAIN"/>`.

Exemplo a atividade principal do jogo foi `com.unity3d.player.UnityPlayerActivity`

![](https://i.imgur.com/FfOtc1K.png)

Certifique-se de habilitar o Word wrap para facilitar a leitura

![](https://i.imgur.com/7DzU8d0.png)

2. APK Easy Tool, pois pode ler a localização da atividade principal sem descompilar o APK

![](https://i.imgur.com/JQdPjyZ.png)

Anote-o em algum lugar para que você possa se lembrar facilmente
### 2. Fazendo as alterações correspondentes nos arquivos
Descompilar o APK do jogo

Abra o jogo `androidmanifest.xml`

Add the `SYSTEM_ALERT_WINDOW` permissão além de outras permissões se não existir.
Só precisamos de uma permissão.
Não importa onde você o coloque, desde que esteja acima da tag do aplicativo

```
<uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW"/>
```

![](https://i.imgur.com/XOxLU91.png)

Adicione o serviço acima do final da tag do aplicativo (altere o nome do pacote do seu menu se você o alterou)
```
<service android:name="uk.lgl.modmenu.FloatingModMenuService" android:enabled="true" android:exported="false" android:stopWithTask="true"/>
```

![](https://i.imgur.com/rw0hawa.png)

Agora precisamos chamar sua atividade do menu mod

Existem 2 maneiras de chamar sua atividade do menu mod. Escolha um deles que você gosta de experimentar. Não sei? basta escolher o MÉTODO 1

**METHOD 1**

Desta forma simples, vamos chamar `MainActivity.java`. `MainActivity.java` nunca será usado

Localize o caminho da atividade principal do jogo e abra o arquivo **smali**.
Se o jogo tiver multi dexes, ele pode estar localizado em smali_classes2.. por favor verifique todos

Com o caminho da atividade principal do jogo alvo que determinamos anteriormente `com.unity3d.player.UnityPlayerActivity`.
 Pense nisso como um camin `/com/unity3d/player/UnityPlayerActivity.smali`

Abra o arquivo smali da atividade principal, procure pelo método OnCreate e
 cole este código dentro (altere o nome do pacote se você o alterou)
```
invoke-static {p0}, Luk/lgl/MainActivity;->Start(Landroid/content/Context;)V
```
 
![](https://i.imgur.com/7CxTCl8.png)

Salve o arquivo

**METHOD 2**

Você pode seguir isso se o primeiro método realmente falhar, ou se você realmente quiser usar `MainActivity.java` 
por uma razão. Como isso envolve a mudança de atividades, pode causar alguns problemas.

On your `MainActivity.java`, coloque a atividade principal do jogo para `public String GameActivity`

![](https://i.imgur.com/jdacwvH.png)

Descomente este código

```
Toast.makeText(MainActivity.this, "Error. Game's main activity does not exist", Toast.LENGTH_LONG).show();
```

On `androidmanifest.xml`, remove `<action android:name="android.intent.action.MAIN"/>` da atividade do jogo, assim:

![](https://i.imgur.com/z1RxPjc.png)

Se você não remover `<action android:name="android.intent.action.MAIN"/>` 
da atividade do jogo, seu menu não será iniciado. `androidmanifest.xml` só pode conter um 
`<action android:name="android.intent.action.MAIN"/>`

perto do final da etiqueta do aplicativo application tag `</application>`, 
adicione sua atividade principal acima dela. `uk.lgl.MainActivity` é sua atividade principal

```xml
<activity android:configChanges="keyboardHidden|orientation|screenSize" android:name="uk.lgl.MainActivity">
     <intent-filter>
         <action android:name="android.intent.action.MAIN"/>
         <category android:name="android.intent.category.LAUNCHER"/>
     </intent-filter>
</activity>
```

![](https://i.imgur.com/33lMPhc.png)

Salve o arquivo
NÃO use os dois métodos ao mesmo tempo

### 3. Building your project and copying files

Build the project to the APK file.
**Build** -> **Build Bundle(s)/APK(s)** -> **Build APK(s)**

If no errors occured, you did everything right and build will succeded. You will be notified that it build successfully

![](https://i.imgur.com/WpSKV1L.png)

Click on **locate** to show you the location of **build.apk**. It is stored at `(your-project)\app\build\outputs\apk\app-debug.apk`

![](https://i.imgur.com/wBTPSLi.png)

Decompile your **app-debug.apk**.

Copy your mod menu from decompiled app-debug.apk smali to the game's smali folder. Example ours is uk.lgl.modmenu, we copy the `uk` folder from **app-debug** `(app-debug\smali\uk)` to the game's decompiled directory `(game name)\smali`

![](https://i.imgur.com/aO6eEab.png)
 
If the game have multidexes, just add your smali to the last `smali_classes` if possible to prevent compilation errors such as `Unsigned short value out of range: xxxxx` (Smali limit error)

Copy the library file (.so) from **app-debug.apk** to the target game. Make sure to copy .so to the correct architecture
armeabi-v7a is armeabi-v7a, arm64-v8a is arm64-v8a, and so on.

PUTTING THE .SO file ON A WRONG ARCHITECTURE WILL RESULT A CRASH!
 
![](https://i.imgur.com/oZq1Wq7.png)
 
### 4. Compiling game apk
 
Agora compile e assine o apk e instale-o no seu dispositivo

Parabéns. Você implementou com sucesso um menu mod.

Falha na compilação? leia o log e procure no Google

Se você enfrentar algum problema, leia as [FAQ](#faq)

# Loading lib without mod menu

Basta ligar para o `LoadLibOnly` in the `OnCreate` method if you want to load your hacks without mod menu
```
    invoke-static {p0}, Luk/lgl/MainActivity;->LoadLibOnly(Landroid/content/Context;)V
```

Make sure to delete `modmenu` folder from the smali to avoid reaching the method limit of the smali classes (limit is 65535)

# FAQ
## My game crashing or freezing/My mod menu does not work
There are many reasons why, it could be your code fault, wrong offsets, bad c++ code, bad layout implementations, game protections etc.

First of all, check logcat on Android Studio to see the error logs. Connect your device/reboot emulator to reconnect, open **Logcat** window from below, and select your device, process and filter to **Error** and reproduce your problem. Once you do, you can see the errors in logcat

![](https://i.imgur.com/cutKC29.png)

Then search the error on Google. Contact me or report issues if you can't find the answers

If the game crashes or freezing while playing, check if your patches and hooks are correct. For hooks, write down the logs such as `LOGD("whatever");` like this below:

```
bool get_BoolExample(void *instance) {
    LOGD("BoolExample 1");
    if (instance != NULL && featureHookToggle) {
        LOGD("BoolExample 2");
        return true;
    }
    LOGD("BoolExample 3");
    return old_get_BoolExample(instance);
}
```

Recompile and check the logcat, to see what part of your code faced the problem.

Logcat may also report `CRASH` if lib crashed, caused by hooking

See more about logcat: https://developer.android.com/studio/debug/am-logcat

If you believe the game has protection, try recompile APK without mod and install to see if it crash. We can't help you bypassing protections

### I have a problem decompiling or compiling APK file
Check if apk is not protected. If not, search for the related issues on Google or on Apktool Github page: https://github.com/iBotPeaches/Apktool/issues

### I'm getting an error `Unsigned short value out of range: 65536` if I compile
The method index can't fit into an unsigned 16-bit value, means you have too many methods in the smali due to the limit 65535. Place your code on other classes, such as smali_classes2 instead. This work for Android 5 (Lollipop) and above only.

### I'm getting an error `ERROR: executing external native build for ndkBuild Android.mk. Affected Modules: app`
See: https://github.com/LGLTeam/Android-Studio-Solutions/wiki/Executing-external-native-build-for-ndkBuild-Android.mk

### I'm getting strange issues on Android Studio or Gradle
See: https://github.com/LGLTeam/Android-Studio-Solutions/wiki

### How to add colored text on JNI toast?
It is not implemented yet, and we don't have enough knowledge in JNI porting to do this

But it is deprecated in API level 30/Android 11, means custom toast will not work, so we will not implement it

See: https://developer.android.com/reference/android/widget/Toast#getView()

### How can I protect my dex and/or lib?

We will not mention their names, but you can search for that on Github. Using chinese tools may inject malwares and spywares in APK. We highly suggest to not use them, and please don't ask us.

There is no need to protect dex since there are nothing important in java/smali codes. All the important codes such as offsets are in the lib file and they are protected enough

### How to get older version of the template? or how to see updates/commits?

Go to the commit page https://github.com/LGLTeam/Android-Mod-Menu/commits/master

### Can I compile this project on Android using AIDE?

Likely yes and no, but we don't support AIDE at this time

### How can I соntact you?
You can соntact me via Tеlеgram or Disсоrd.

<details>
<summary>Contact:</summary>
Before you contact, please make sure you have readed everything and looking on Google before contacting

Newbies who do not understand anything must NOT соntact. You will be BLOCKED if you ask/beg to teach/spoonfeed. Why? Because we have gotten so many newbie kids who wouldn't know nothing about modding but attempt to try this for nothing, and come to me and begging and spamming for help. We are getting tired of this now. DON'T be that toxic kid please

Speak english only please. Speaking in other language will be ignored

Thanks!

Tеlеgram: @ThеᒪGᒪ

Disсоrd: ᒪGᒪ#6844
</details>

### Can you help me mod (name of game)?

Noob, we are not spoonfeeding. Don't соntact if you don't know how to mod games.
                              
Instead, try to find a couple of tutorials to learn and mod the game yourself. It's a lot easier than you think. If you can't, search on the internet and you should find a couple of forums where you can ask your questions.

### Do you have project of someones mod menu including game codes for example MITO Team mod?

No, because they used this template and they created their own mod with it, we don't support nor work with them. Ask the right owner who have them, example if mod is created by MITO Team, ask MITO Team. We are the wrong persons to ask.

### Where can I learn hooking?

* https://piin.dev/basic-hooking-tutorial-t19.html
* https://iosgods.com/topic/65529-instance-variables-and-function-pointers/
* https://guidedhacking.com/threads/android-function-pointers-hooking-template-tutorial.14771/
* http://www.cydiasubstrate.com/api/c/MSHookFunction/
* https://www.cprogramming.com/tutorial/function-pointers.html

# Credits/Acknowledgements
Thanks to the following individuals whose code helped me develop this mod menu

* Octowolve/Escanor - Mod menu: https://github.com/z3r0Sec/Substrate-Template-With-Mod-Menu and Hooking: https://github.com/z3r0Sec/Substrate-Hooking-Example
* VanHoevenTR - Mod menu - https://github.com/LGLTeam/VanHoevenTR_Android_Mod_Menu
* MrIkso - First mod menu template https://github.com/MrIkso/FloatingModMenu
* MJx0 A.K.A Ruit - https://github.com/MJx0/KittyMemory
* Rprop - https://github.com/Rprop/And64InlineHook
* Some modders for suggestions and ideas :)