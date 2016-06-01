


char con628(char c6)  
{  
    char rtn = '\0';  
    if (c6 < 26) rtn = c6 + 65;  
    else if (c6 < 52) rtn = c6 + 71;  
    else if (c6 < 62) rtn = c6 - 4;  
    else if (c6 == 62) rtn = 43;  
    else rtn = 47;  
    return rtn;  
}  

void base64(char *dbuf, char *buf128, int len)  
{  
    struct data6 *ddd = NULL;  
    int i = 0;  
    char buf[256] = {0};  
    char *tmp = NULL;  
    char cc = '\0';  
    memset(buf, 0, 256);  
    strcpy(buf, buf128);  
    for(i = 1; i <= len/3; i++)  
    {  
    tmp = buf+(i-1)*3;  
    cc = tmp[2];  
    tmp[2] = tmp[0];  
    tmp[0] = cc;  
    ddd = (struct data6 *)tmp;  
    dbuf[(i-1)*4+0] = con628((unsigned int)ddd->d1);  
    dbuf[(i-1)*4+1] = con628((unsigned int)ddd->d2);  
    dbuf[(i-1)*4+2] = con628((unsigned int)ddd->d3);  
    dbuf[(i-1)*4+3] = con628((unsigned int)ddd->d4);  
    }  
    if(len%3 == 1)  
    {  
    tmp = buf+(i-1)*3;  
    cc = tmp[2];  
    tmp[2] = tmp[0];  
    tmp[0] = cc;  
    ddd = (struct data6 *)tmp;  
    dbuf[(i-1)*4+0] = con628((unsigned int)ddd->d1);  
    dbuf[(i-1)*4+1] = con628((unsigned int)ddd->d2);  
    dbuf[(i-1)*4+2] = '=';  
    dbuf[(i-1)*4+3] = '=';  
    }  
    if(len%3 == 2)  
    {  
    tmp = buf+(i-1)*3;  
    cc = tmp[2];  
    tmp[2] = tmp[0];  
    tmp[0] = cc;  
    ddd = (struct data6 *)tmp;  
    dbuf[(i-1)*4+0] = con628((unsigned int)ddd->d1);  
    dbuf[(i-1)*4+1] = con628((unsigned int)ddd->d2);  
    dbuf[(i-1)*4+2] = con628((unsigned int)ddd->d3);  
    dbuf[(i-1)*4+3] = '=';  
    }  
    return;  
}  