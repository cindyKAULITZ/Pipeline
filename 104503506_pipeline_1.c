#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
void getBin(int num, char *str)
{
  *(str+5) = '\0';
  int mask = 0x10 << 1;
  while(mask >>= 1)
    *str++ = !!(mask & num) + '0';
}
void substr(char *dest, const char* src, unsigned int start, unsigned int cnt) {
   strncpy(dest, src + start, cnt);
   dest[cnt] = 0;
 }
int convertBinaryToDecimal(long long n)
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}


int main(){
    int i,cc=1;
    long k;
    char temp;
    char instruction[100]={'\0'};
    char instruction2[100]={'\0'};
    char op[6];
    FILE *iptr = fopen("General.txt","r");
    FILE *optr = fopen("GenResult.txt","w");
    int reg[10]={0,9,8,7,1,2,3,4,5,6};
    int mem[5]={5,9,4,8,7};

    for(i=0;!feof(iptr);i++){
        temp=fgetc(iptr);
        instruction[i]=temp;
    }
char printsig1[5];
char printsig2[2];
char teemp[32]={'\0'};
int flag=0;
char inst_op[6]={'0'};
char inst_rs[5]={'0'};
char inst_rt[5]={'0'};
char inst_rd[5]={'0'};
char inst_funct[6]={'\0'};
char inst_imm[16]={'0'};
char inst_fetch[32]={'\0'};
char ctrl_sig[9];
int rsinst;
int instcount=0;
int inst_type=0;
char ifid_inst[32]={'\0'};
int memwb_rtd=0;
int memwb_aluout=0;
int memwb_readdata=0;
int exemem_insttype=0;
int exemem_aluout=0;
int exemem_rtd=0;
int exemem_writedata=0;
char memwb_ctrlsig[2];
char exemem_ctrlsig[5];
int memwb_insttype=0;
int idexe_rs=0;
int idexe_rt=0;
int idexe_rd=0;
int idexe_signext=0;
int idexe_insttype=0;
char idexe_ctrlsig[9];
int idexe_readdata1=0;
int idexe_readdata2=0;
int ifid_pc=0;
int j;
char temp1[10]={'\0'};
 /*for(i=instcount,j=0;i<instcount+32;i++,j++){
            inst_fetch[j]=instruction[i];
        }
       // strncpy(ifid_inst,inst_fetch,32);
       // fprintf(optr,"ifid_inst: %s\n",ifid_inst);
        for(i=instcount,j=0;i<instcount+6,j<6;i++,j++){
            inst_op[j]=instruction[i];
        }
        for(i=(instcount+25),j=0;i<(instcount+25+6),j<6;i++,j++){
            inst_funct[j]=instruction[i];
        }


        if(strncmp(inst_op,"000000",6)==0){
         //   fprintf(optr,"RTYPE: %s",inst_op);
            if(strncmp(inst_funct,"100000",6)==0){//add
                inst_type=0;
            }
            else if(strncmp(inst_funct,"100010",6)==0){//sub
                inst_type=1;
            }
            else if(strncmp(inst_funct,"100100",6)==0){//and
                inst_type=2;
            }
            else if(strncmp(inst_funct,"100101",6)==0){//or
                inst_type=3;
            }
            else if(strncmp(inst_funct,"101010",6)==0){//slt
                inst_type=4;
            }

            strcpy(ctrl_sig,"110000010");
         //   fprintf(optr,"\nCTRLSGNAL: %s",ctrl_sig);
        }
        else{
          //  fprintf(optr,"WWDWEGRGTYPE: %s",inst_op);
            if(strncmp(inst_op,"100011",6)==0){//lw
                inst_type=5;
                 strcpy(ctrl_sig,"000101011");
            }
            else if(strncmp(inst_op,"101011",6)==0){//sw
                inst_type=6;
                 strcpy(ctrl_sig," 0010010 ");
            }
            else if(strncmp(inst_op,"001000",6)==0){//addi
                inst_type=7;
                strcpy(ctrl_sig,"000100010");
            }
            else if(strncmp(inst_op,"001100",6)==0){//andi
                inst_type=8;
                strcpy(ctrl_sig,"011100010");
            }
            else if(strncmp(inst_op,"000101",6)==0){//bne
                inst_type=9;
                strcpy(ctrl_sig," 0100000 ");
            }
        }
      //  strncpy(ifid_inst,inst_fetch,sizeof(ifid_inst));
      //  fprintf(optr,"%s\n",ifid_inst);
        instcount+=33;*/
while(flag==0){


//do wb stage
        if(memwb_insttype!=5&&memwb_insttype!=6&&memwb_insttype!=9){
            reg[memwb_rtd]=memwb_aluout;
        }
        else if(memwb_insttype==5){
            reg[memwb_rtd]=memwb_readdata;
        }

// mem/wb
    if(exemem_insttype==5){
        memwb_readdata=mem[exemem_aluout];
        memwb_aluout=exemem_aluout;
        memwb_rtd=exemem_rtd;
    }
    else if(exemem_insttype==6){
        mem[exemem_aluout]=exemem_writedata;
        memwb_readdata=0;
        memwb_aluout=exemem_aluout;
        memwb_rtd=exemem_rtd;
    }
    else{
        memwb_readdata=0;
        memwb_aluout=exemem_aluout;
        memwb_rtd=exemem_rtd;
    }
       // memset(memwb_ctrlsig,'0',sizeof(memwb_ctrlsig));
        substr(memwb_ctrlsig,exemem_ctrlsig,3,sizeof(memwb_ctrlsig));
        for(i=0;i<2;i++)
            printsig2[i]=memwb_ctrlsig[i];
        memwb_insttype=exemem_insttype;
// exe/mem
        exemem_writedata=reg[idexe_readdata2];
        if(idexe_insttype==0){                                      //compare the instruction type to do different thing
            exemem_aluout=idexe_readdata1+idexe_readdata2;
            exemem_rtd=idexe_rd;
        }
        else if(idexe_insttype==1){
            exemem_aluout=idexe_readdata1-idexe_readdata2;
            exemem_rtd=idexe_rd;
        }
        else if(idexe_insttype==2){
            exemem_aluout=(char)idexe_readdata1&(char)idexe_readdata2;
            exemem_rtd=idexe_rd;
        }
        else if(idexe_insttype==3){
            exemem_aluout=(char)idexe_readdata1|(char)idexe_readdata2;
            exemem_rtd=idexe_rd;
        }
        else if(idexe_insttype==4){
            if(idexe_readdata1-idexe_readdata2<0){
                exemem_aluout=1;
            }
            else
                exemem_aluout=0;
                exemem_rtd=idexe_rd;

        }
        else if(idexe_insttype==5){
           exemem_aluout=idexe_readdata1+idexe_signext;
           exemem_writedata=exemem_aluout;
           exemem_rtd=idexe_rt;

        }
        else if(idexe_insttype==6){
           exemem_aluout=idexe_readdata1+idexe_signext;
           exemem_writedata=reg[idexe_rt];
           exemem_rtd=idexe_rt;
        }
        else if(idexe_insttype==7){
           exemem_aluout=idexe_readdata1+idexe_signext;
           exemem_rtd=idexe_rt;
        }
        else if(idexe_insttype==8){
           exemem_aluout=(char)idexe_readdata1&(char)idexe_signext;
           exemem_rtd=idexe_rt;
        }
        else if(idexe_insttype==9){
           exemem_aluout=idexe_readdata1+idexe_signext;
           exemem_rtd=reg[idexe_rt];
        }
        exemem_writedata=0;
        substr(exemem_ctrlsig,idexe_ctrlsig,4,sizeof(exemem_ctrlsig));
          for(i=0;i<5;i++)
            printsig1[i]=exemem_ctrlsig[i];
        exemem_insttype=idexe_insttype;
        //fprintf(optr,"****Ctrl Signal :%s\n",exemem_ctrlsig);
// id/exe
    substr(inst_rs,ifid_inst,6,sizeof(inst_rs));
      idexe_rs=convertBinaryToDecimal(atoi(inst_rs));     //rs,rt,rd,signext to decimal value

      substr(inst_rt,ifid_inst,11,sizeof(inst_rt));
      idexe_rt=convertBinaryToDecimal(atoi(inst_rt));

      substr(inst_rd,ifid_inst,16,sizeof(inst_rd));
      idexe_rd=convertBinaryToDecimal(atoi(inst_rd));

       substr(inst_imm,ifid_inst,16,sizeof(inst_imm));
      idexe_signext=convertBinaryToDecimal(atoi(inst_imm));
      substr(idexe_ctrlsig,ctrl_sig,0,sizeof(idexe_ctrlsig));
      idexe_readdata1=reg[idexe_rs];
      idexe_readdata2=reg[idexe_rt];
      idexe_insttype=inst_type;

// if/id
      // fprintf(optr,"*RSSSSS :%s\n",inst_rs);
        ifid_pc=ifid_pc+4;
       // strcpy(ifid_inst,inst_fetch);


//fetch
fprintf(optr,"\nCC: %d\n",cc);
        fprintf(optr,"\nRegister:\n");
          for(i=0;i<10;i++){
           fprintf(optr,"$%d: %d\n",i,reg[i]);

        }
         fprintf(optr,"\nData Memory:\n");
        for(i=0;i<5;i++){
           fprintf(optr,"0x%02X: %d\n",i*4,mem[i]);
        }
        fprintf(optr,"\nIF/ID :\n");
        fprintf(optr,"PC :%d\n",ifid_pc);
       // fprintf(optr,"ifid_inst: %s",ifid_inst);
        //判斷opcode   如果=0 (rtype)判斷func   如果!=0(itype)看是哪個指令
        int j;
        substr(ctrl_sig,"000000000",0,sizeof(ctrl_sig));
        if(instcount>=strlen(instruction)){
            for(i=instcount,j=0;i<instcount+32;i++,j++){
            inst_fetch[j]='0';
            inst_type=-1;

        }
        substr(ifid_inst,inst_fetch,0,sizeof(ifid_inst));
            fprintf(optr,"Instruction :%s\n",ifid_inst);
        }
        else{

        for(i=instcount,j=0;i<instcount+32;i++,j++){
            inst_fetch[j]=instruction[i];
           // teemp[j]=inst_fetch[j];
        }
        substr(ifid_inst,inst_fetch,0,sizeof(ifid_inst));
      //  strncpy(ifid_inst,teemp,sizeof(ifid_inst));
       // k=atof(teemp);
        fprintf(optr,"*Instruction :%s\n",ifid_inst);
       // fprintf(optr,"ifid_inst: %s\n",ifid_inst);
        for(i=instcount,j=0;i<instcount+6,j<6;i++,j++){
            inst_op[j]=instruction[i];
        }
        for(i=(instcount+25),j=0;i<(instcount+25+6),j<6;i++,j++){
            inst_funct[j]=instruction[i];
        }
    /*    for(i=(instcount+6),j=0;i<(instcount+11),j<5;i++,j++){
            temp1[j]=teemp[i];
            inst_rs[j]=temp1[j];
        }
        fprintf(optr,"*RSSSSS :%s\n",inst_rs);*/



        if(strncmp(inst_op,"000000",6)==0){
         //   fprintf(optr,"RTYPE: %s",inst_op);
            if(strncmp(inst_funct,"100000",6)==0){//add
                inst_type=0;
            }
            else if(strncmp(inst_funct,"100010",6)==0){//sub
                inst_type=1;
            }
            else if(strncmp(inst_funct,"100100",6)==0){//and
                inst_type=2;
            }
            else if(strncmp(inst_funct,"100101",6)==0){//or
                inst_type=3;
            }
            else if(strncmp(inst_funct,"101010",6)==0){//slt
                inst_type=4;
            }
           // memset(ctrl_sig,'\0',9);
            substr(ctrl_sig,"110000010",0,sizeof(ctrl_sig));
         //   fprintf(optr,"\nCTRLSGNAL: %s",ctrl_sig);
        }
        else{
          //  fprintf(optr,"WWDWEGRGTYPE: %s",inst_op);
            if(strncmp(inst_op,"100011",6)==0){//lw
                inst_type=5;
                substr(ctrl_sig,"000101011",0,sizeof(ctrl_sig));
            }
            else if(strncmp(inst_op,"101011",6)==0){//sw
                inst_type=6;
                substr(ctrl_sig," 0010010 ",0,sizeof(ctrl_sig));

            }
            else if(strncmp(inst_op,"001000",6)==0){//addi
                inst_type=7;
                substr(ctrl_sig,"000100010",0,sizeof(ctrl_sig));

            }
            else if(strncmp(inst_op,"001100",6)==0){//andi
                inst_type=8;
                substr(ctrl_sig,"011100010",0,sizeof(ctrl_sig));

            }
            else if(strncmp(inst_op,"000101",6)==0){//bne
                inst_type=9;
                substr(ctrl_sig," 0100000 ",0,sizeof(ctrl_sig));

            }
        }
        }

       // fprintf(optr,"Instruction :%s\n",inst_fetch);
     // fprintf(optr,"*Instruction :%s\n",teemp);
        fprintf(optr,"\nID/EXE :\n");
        fprintf(optr,"ReadData1 :%d\nReadData2 :%d\n",idexe_readdata1,idexe_readdata2);
        fprintf(optr,"Sign_ext :%d\n",idexe_signext);
        fprintf(optr,"Rs :%d\nRt :%d\nRd :%d\n",idexe_rs,idexe_rt,idexe_rd);
        fprintf(optr,"Ctrl Signal :%s\n",idexe_ctrlsig);
        fprintf(optr,"\nEXE/MEM :\n");
        fprintf(optr,"AluOut :%d\n",exemem_aluout);
        fprintf(optr,"Writedata:%d\n",exemem_writedata);
        fprintf(optr,"Rt/Rd :%d\n",exemem_rtd);
        fprintf(optr,"Ctrl Signal :%s\n",printsig1);
        fprintf(optr,"\nMEM/WB :\n");
        fprintf(optr,"Readdata : %d\n",memwb_readdata);
        fprintf(optr,"AluOut :%d\n",memwb_aluout);
        fprintf(optr,"Rt/Rd :%d\n",memwb_rtd);
        fprintf(optr,"Ctrl Signal :%s\n",printsig2);
        fprintf(optr,"\n==============================================\n");
        //print this cycle
        //fprintf("\nCC:");

            instcount+=33;
            cc+=1;
             if(memwb_insttype==-1)
            flag=1;

}

fclose(iptr);

}
