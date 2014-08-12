; created at 2014/08/11 by cmooony@gmail.com


#define MyAppName "Keepod OS Installer"
#define MyAppVersion "1.0.0.0"
#define MyAppPublisher "Keepod"
#define MyAppURL "https://github.com/Keepod/keepod-installer"
#define MyAppExeName "keepod-installer.exe"

; ���������qtĿ¼/����Ŀ¼
; #define QT_PATH "E:\Qt\4.8.6"
#define MyAppFilePath "bin" 

[Setup]
; ע: AppId��ֵΪ������ʶ��Ӧ�ó���
; ��ҪΪ������װ����ʹ����ͬ��AppIdֵ��
; (�����µ�GUID����� ����|��IDE������GUID��)
AppId={{26375A10-A3AA-40BB-9A4F-59634B78292A}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}

DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes 

UsePreviousAppDir=yes

;LicenseFile={#MyAppFilePath}\license.txt
;InfoBeforeFile={#MyAppFilePath}\info.b.txt
;InfoAfterFile={#MyAppFilePath}\info.a.txt
OutputDir=.
OutputBaseFilename=Keepod OS Installer
SetupIconFile={#MyAppFilePath}\unetbootin_64.ico
Compression=lzma
SolidCompression=yes
PrivilegesRequired=admin


[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Languages\ChineseSimp.isl"
; Name: "chinesestrad"; MessagesFile: "compiler:Languages\ChineseTrad.isl"
; Name: "english"; MessagesFile: "compiler:Languages\English.isl"
; Name: "brazilianportuguese"; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"
; Name: "catalan"; MessagesFile: "compiler:Languages\Catalan.isl"
; Name: "corsican"; MessagesFile: "compiler:Languages\Corsican.isl"
; Name: "czech"; MessagesFile: "compiler:Languages\Czech.isl"
; Name: "danish"; MessagesFile: "compiler:Languages\Danish.isl"
; Name: "dutch"; MessagesFile: "compiler:Languages\Dutch.isl"
; Name: "finnish"; MessagesFile: "compiler:Languages\Finnish.isl"
; Name: "french"; MessagesFile: "compiler:Languages\French.isl"
; Name: "german"; MessagesFile: "compiler:Languages\German.isl"
; Name: "greek"; MessagesFile: "compiler:Languages\Greek.isl"
; Name: "hebrew"; MessagesFile: "compiler:Languages\Hebrew.isl"
; Name: "hungarian"; MessagesFile: "compiler:Languages\Hungarian.isl"
; Name: "italian"; MessagesFile: "compiler:Languages\Italian.isl"
; Name: "japanese"; MessagesFile: "compiler:Languages\Japanese.isl"
; Name: "norwegian"; MessagesFile: "compiler:Languages\Norwegian.isl"
; Name: "polish"; MessagesFile: "compiler:Languages\Polish.isl"
; Name: "portuguese"; MessagesFile: "compiler:Languages\Portuguese.isl"
; Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"
; Name: "scottishgaelic"; MessagesFile: "compiler:Languages\ScottishGaelic.isl"
; Name: "serbiancyrillic"; MessagesFile: "compiler:Languages\SerbianCyrillic.isl"
; Name: "serbianlatin"; MessagesFile: "compiler:Languages\SerbianLatin.isl"
; Name: "slovenian"; MessagesFile: "compiler:Languages\Slovenian.isl"
; Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"
; Name: "turkish"; MessagesFile: "compiler:Languages\Turkish.isl"
; Name: "ukrainian"; MessagesFile: "compiler:Languages\Ukrainian.isl"

[Files]
; QT ���
;Source: "{#QT_PATH}\bin\QtCore4.dll"; DestDir: "{app}"; Flags: ignoreversion
;Source: "{#QT_PATH}\bin\QtGui4.dll"; DestDir: "{app}"; Flags: ignoreversion
;Source: "{#QT_PATH}\bin\QtNetwork4.dll"; DestDir: "{app}"; Flags: ignoreversion
; C++��׼�� ���
;Source: "{#QT_PATH}\bin\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
;Source: "{#QT_PATH}\bin\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
;Source: "{#QT_PATH}\bin\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
; ����
Source: "{#MyAppFilePath}\*.exe"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "{#MyAppFilePath}\*.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "{#MyAppFilePath}\*.txt"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
; ע��: ��Ҫ���κι���ϵͳ�ļ���ʹ�á�Flags: ignoreversion��
 
;[Tasks]
;Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked;
;Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

;[Icons]
; ��ʼ�˵�
;Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Flags: runminimized;
;Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
;Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"

; �����ݷ�ʽ
;Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
;Name: "{userdesktop}\{#MyAppName}";Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"; Tasks: desktopicon
;Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}";Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

