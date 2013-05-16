class file_send
{
    public:
        SOCKET send_s; //The socket that used for sending which is established previously
        char * filename; //The full path of the file that the client requested
        void send_file()
        {
            percentage=0;
            FILE * pFile=fopen(filename,"rb"); 
            fseek(pFile,0,SEEK_END);
            flen=ftell(pFile);
            cout<<"File length is :"<<flen<<endl;
            rewind(pFile);
            partsnum=flen/BUF_LEN+1;
            send(send_s,(char *)(&partsnum),sizeof(partsnum),0);
            cout<<"File parts num:"<<partsnum<<endl;
            cout<<"File name:"<<filename<<endl;
            str=new char[BUF_LEN];
            int i;
            if(partsnum>1)
            {
                plen=BUF_LEN;
            }
            for(i=0;i<partsnum;i++)
            {
                if(i==(partsnum-1))
                {
                    plen=flen%BUF_LEN;
                }
                fread(str,1,BUF_LEN,pFile);// read part file to str
                send(send_s,(char *)(&plen),sizeof(plen),0); // send length of part file
                send(send_s,str,plen,0); // send str(part file)
                if(percentage!=(i*100)/partsnum)
                {
                    percentage=(i*100)/partsnum;
                    cout<<percentage<<"\%complete!"<<endl;
                }
            }
            fclose(pFile);
        }
    private:
        int flen,plen,partsnum,percentage;
        char * str;
};

class file_rev
{
    public:
        SOCKET rev_s;
        char * filename;
        void rev_file()
        {
            FILE * fn=fopen(filename,"wb");
            recv(rev_s,(char *)(&partsnum),sizeof(partsnum),0);
            cout<<"File parts num:"<<partsnum<<endl;
            int i;
            for(i=0;i<partsnum;i++)
            {
                recv(rev_s,(char *)(&flen),sizeof(flen),0); 
                buf=new char[flen];
                recv(rev_s,buf,flen,0);
                //cout<<"File parts received:"<<i<<endl;
                //cout<<"File parts length:"<<flen<<endl; 
                fwrite(buf,1,flen,fn);
            }
            fclose(fn);
        }
    private:
        int flen,plen,partsnum;
        char * buf;
};

