#include "com_yh_NvdimmUtils.h"
#include <stdint.h>
#include <ArxcisAPI.h>
#include <stdio.h>
#include<string.h>

#define MAX_DIMMS 32
#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

JNIEXPORT void JNICALL Java_com_yh_NvdimmUtils_write
  (JNIEnv * env , jobject obj, jbyteArray array, jint off, jint len){

    uint64_t Address,Length;  //allocate the size of mem in nvdimm 
    int32_t numDimms ;
    int32_t returnValue = 0;
    int saveType ;
    uint8_t configByte;
    uint8_t lDimmNum=0;
    int mem_pattern = true;
    int dimm = 0; //a value of zero means to apply to all dimms detected
    

    //open and close buffer
    setbuf(stdout,NULL);


   //detect the NVDIMM Address is start address ,Length is size
    numDimms= ArxNVDimmsDetected(&Address,&Length);
    printf("Length=%d\n",Length);
    if(numDimms<0)
    {
        printf("FAIL: Arm: ArxNVDimmsDetected failed returned %d\n",numDimms);
        return; 
    }


    saveType= POWER_FAIL_SAVE | HOST_INTERRUPT_SAVE;
    printf("Arm NVDIMMs for Host Interrupt or power fail detected\n");
    
    //set the save type of NVDIMM
    returnValue = ArxEnableSave(lDimmNum,saveType);
    if(returnValue!=ARX_SUCCESS){
        printf("FAIL: ArxEnableSave failed on one or more dimms returned %d\n",returnValue);
        return; 
    }

  
     char *word;
     char *lva,*charlp;

     word = (*env)->GetByteArrayElements(env,array,0);
     lva = ArxMalloc(1,&Length);
     printf("the allocated space in nvdimm is %d\n",&Length);
     
     if(Length < len){
      printf("cannot get enough space in nvdimm to write");
      return;
      }

     charlp = lva;

     int i;
     for (i=off; i<len; i++){
      *charlp++ = word[i];      
 
}
   
}
