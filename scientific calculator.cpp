#include<stdio.h>
#include<math.h>
#include<dos.h>
#include<string.h>
#include<graphics.h>
#include<stdlib.h>
#define SUM 1

class mouse
{
    public:
        union REGS i,o;       // UNION of type REGS
        int button,mousex,mousey;
        initmouse()
        {                            //ax,bx,cx,dx integers
            i.x.ax=0;
            int86(0x33,&i,&o);
            return(o.x.ax);
        }
        showmouse_pointer()
        {                                //mouse programmng
            i.x.ax=1;
            int86(0x33,&i,&o);  
            return 0;
        }
        void hidemouse_pointer()
        {
            i.x.ax=2;
            int86(0x33,&i,&o);
        }
        getmousepos(int *button,int *x,int *y)
        {
            i.x.ax=3;          // coordinates 
            int86(0x33,&i,&o);
            *button=o.x.bx;
            *x=o.x.cx;   //x coordinate 
            *y=o.x.dx;  //y coordinate
            return 0;
        }
};
class strn
{
    public:
        void strcut(char *a);
        void del(char *d);
};
void strn::strcut(char *a)
{
    a[9]='\0';                    
}
void strn::del(char *d)
{
    d[strlen(d)-1]='\0';  // function for the delete button
}

class calc:public mouse,public strn
{
    private:
        int gd,gm,x,y,i,j;
    public:
        void display();
        void key();
      
    void button(int tx,int ty,int bx,int by,int lx,int ly,int lx1,int ly1,char *s,char *s1); 
};

void calc::display()
{
    
    key();

}
void calc::key()
{
    setcolor(9);
  
    outtextxy(350,80,"MY SCIENTIFIC CALCULATOR");

    outtextxy(555,202,"ON");
    outtextxy(498,202,"DEL");
    outtextxy(558,245,"/");   // visible written text on the console 
    outtextxy(558,288,"-");
                                        //  outtext x,y the position of the button at the   x and y coordinate 
    outtextxy(505,245,"*");
    outtextxy(505,288,"+");
    outtextxy(498,331,"ANS");
    outtextxy(401,329,"0");
    outtextxy(445,331,".");
     outtextxy(454,202,"9");
 outtextxy(401,202,"8");
outtextxy(348,202,"7");
outtextxy(348,245,"4");
outtextxy(401,245,"5");
  outtextxy(454,245,"6");
 outtextxy(348,288,"1");
outtextxy(401,288,"2");
 outtextxy(454,288,"3");
outtextxy(401,329,"0");
    
}


void calc::button(int tx,int ty,int bx,int by,int lx,int ly,int lx1,int ly1,char *s,char *s1)
{

            hidemouse_pointer();
            setfillstyle(1,4);//changing the inside color of the button
            bar3d(tx,ty,bx,by,1,1);   
            setcolor(9); // changing the color of the text
            outtextxy(lx,ly,s);
            setcolor(0);   // changing the color of the boundry of the button
            outtextxy(lx1,ly1,s1);
            showmouse_pointer();
}

void main()
{
int q, v;
q = DETECT;
initgraph(&q,&v,"..\\bgi");
rectangle (300,25,600,400); // rectangle around the calculator
setcolor(14);
 
    int mousex,mousey,but;
    int key=0,key1=0;
    int pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1;
    int on=0,sub=0,add=0,mul=0,div=0,equal=0;
    int vx=555,vy=152,count=0;
    long int var1,var2;
    double temp1,ans=0,a=0,b=0,c=0,d=0,e=0,m=0;
    char *input;
    input[0]='\0';       


    char *paste_string,*paste_string1;
    char *svar,*ms,*stemp;

    int operation=0;
    calc ob;
    ob.display();
    ob.initmouse();

    ob.showmouse_pointer();

    for(;;)
    {
        ob.getmousepos(&but,&mousex,&mousey);  // for  the position of the mouse


        if(mousex>537&&mousex<587&&mousey>185&&mousey<225)  // condition for if mouse is here  then if the key is not equal to 1 assign key the value of that button
        {

            if(key!=1) // we have initially  declare button as key to  give name to that key not permanently but to apply the conditions of that button  that if mouse points on that button and that button is not active to give conditions  the it should equal its self to key and show and perform its properties
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);    //clicking that button will paste the button as a string on the calculating bar
            key=1;
           
            pointer_x=537;
            pointer_y=185;
            pbx=587;
            pby=225;
            plx=555;
            ply=202;
            paste_string="ON";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(but==1&&on==0)
                on=1;

            if(but==1&&key1!=1) 
            {
                input[0]='\0';
                temp1=0; //temporary variable to store result
                sub=0,add=0,mul=0,div=0,equal=0;
              
                setfillstyle(1,9);
                bar(330,141,586,169);           // calculating bar 
                setcolor(8);
               outtextxy(555,152,"0");
               
                count=0;
               
                key1=1;
                delay(100);
               
            }
            if(but==1&&key1!=1)
            {
                free(input);  //deallocates the memory  which is previously allocated 
                free(paste_string);
                free(paste_string1);
                exit(0);
            }

        }
        else if(mousex>484&&mousex<534&&mousey>185&&mousey<225&&on==1)
        {

            if(key!=2)   
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=2;
         
            pointer_x=484;
            pointer_y=185;
            pbx=534;
            pby=225;
            plx=498;
            ply=202;
            paste_string="DEL";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(but==1&&key1!=2)
            {
               setfillstyle(0,0);
                setfillstyle(1,9);
                bar(330,141,586,169);
                ob.del(input);
                if(input[0]!='\0')
                outtextxy(vx-strlen(input)*8+8,vy,input);    
                else
                outtextxy(555,152,"0");
                count--;
                setcolor(0);
                key1=2;
                delay(200);
                key1=0;
            }


        }
        else if(mousex>428&&mousex<478&&mousey>185&&mousey<225&&on==1)
        {

            if(key!=3)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=3;

            pointer_x=431;
            pointer_y=185;
            pbx=481;
            pby=225;
            plx=454;
            ply=202;
            paste_string="9";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(count<9)
            if(but==1&&key1!=3)
            {
                
setfillstyle(1,9);
                bar(330,141,586,169);
                setcolor(11);
                strcat(input,paste_string);   //  appends the string
                outtextxy(vx-count*8,vy,input);                        // the value of the bar is at vx=555,vy=152,count=0; 
                count++;  //vy will remain same because count *8 wil be subtracted from the bar's  555 and the digit we pressed wil be moved to the previous location of the ist digit
                setcolor(0);
                key1=3;
                delay(200);
                key1=0;
            }

        }
        else if(mousex>378&&mousex<428&&mousey>185&&mousey<225&&on==1)
        {
            if(count<10)
            if(key!=4)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=4;

            pointer_x=378;
            pointer_y=185;
            pbx=428;
            pby=225;
            plx=401;
            ply=202;
            paste_string="8";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(count<9)
            if(but==1&&key1!=4)
            {
                
                setfillstyle(1,9);
                bar(330,141,586,169);
                setcolor(11);
                strcat(input,paste_string);
                outtextxy(vx-count*8,vy,input);
                count++;
               

                key1=4;
                delay(200);
                key1=0;
            }

        }
        else if(mousex>325&&mousex<375&&mousey>185&&mousey<225&&on==1)
        {

            if(key!=5)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=5;

            pointer_x=325;
            pointer_y=185;
            pbx=375;
            pby=225;
            plx=348;
            ply=202;
            paste_string="7";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(but==1&&key1!=5)
            {
               
               setfillstyle(1,9);
                bar(330,141,586,169);
                setcolor(11);
                strcat(input,paste_string);
                outtextxy(vx-count*8,vy,input);
                count++;
                setcolor(0);
                key1=5;
                delay(200);
              
            }

        }
        else if(mousex>325&&mousex<375&&mousey>228&&mousey<271&&on==1)
        {

            if(key!=6)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=6;

            pointer_x=325;
            pointer_y=228;
            pbx=375;
            pby=268;
            plx=348;
            ply=245;
            paste_string="4";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(but==1&&key1!=6)
            {
             
             setfillstyle(1,9);
                bar(330,141,586,169);
                setcolor(11);
                strcat(input,paste_string);
                outtextxy(vx-count*8,vy,input);
                count++;
                setcolor(0);
                key1=6;
                delay(200);
                key1=0;
            }

        }
        else if(mousex>378&&mousex<428&&mousey>228&&mousey<271&&on==1)
        {

            if(key!=7)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=7;

            pointer_x=378;
            pointer_y=228;
            pbx=428;
            pby=268;
            plx=401;
            ply=245;
            paste_string="5";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(but==1&&key1!=7)
            {
                
             setfillstyle(1,9);
                bar(330,141,586,169);
                setcolor(11);
                strcat(input,paste_string);
                outtextxy(vx-count*8,vy,input);
                count++;
                setcolor(0);
                key1=7;
                delay(200);
                key1=0;
            }

        }
        else if(mousex>431&&mousex<481&&mousey>228&&mousey<271&&on==1)
        {

            if(key!=8)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=8;

            pointer_x=431;
            pointer_y=228;
            pbx=481;
            pby=268;
            plx=454;
            ply=245;
            paste_string="6";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(but==1&&key1!=8)
            {
               
              setfillstyle(1,9);
                bar(330,141,586,169);
                setcolor(11);
                strcat(input,paste_string);
                outtextxy(vx-count*8,vy,input);
                count++;
                setcolor(0);
                key1=8;
                delay(200);
                key1=0;
            }

        }
//conditions for multiply
        else if(mousex>484&&mousex<534&&mousey>228&&mousey<268&&on==1)
        {

            if(key!=9)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=9;

            pointer_x=484;
            pointer_y=228;
            pbx=534;
            pby=268;
            plx=505;
            ply=245;
            paste_string="*";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(but==1&&key1!=9)
            {
                temp1=atof(input); // function for converting string to double
                if(mul==0&&equal==1)
                {
                    mul=1;                    //conditions for situations like 5*4+3
                    equal=0;
                    
                }
                else if(add==0&&sub==0&&mul==0&&div==0)
                {
                    ans=temp1;
                    mul=1;
                 
                }
                else if(add==0&&sub==1&&mul==0&&div==0)
                {
                    sub=0;add=0;div=0;mul=1;
                    ans=ans-temp1;
                 
                }
                else if(add==1&&sub==0&&mul==0&&div==0)
                {
                    sub=0;add=0;div=0;mul=1;
                    ans=ans+temp1;
                
                }
                else if(add==0&&sub==0&&mul==0&&div==1)
                {
                    sub=0;add=0;div=0;mul=1;
                    ans=ans/temp1;
               
                }
                else if(mul==1)
                {
                    sub=0;div=0;add=0;
                    ans=ans*temp1;
                
                }
                operation=3;
               
                setcolor(11);
                gcvt(ans,10,input);
              
              
                outtextxy(vx-strlen(input)*8+8,vy,input);
               
                for(int k=0;k<count;k++)
                {
                    input[k]='\0';
                }
                count=0;
                setcolor(0);
                temp1=0;
                key1=9;
                delay(200);
              
            }

        }
        else if(mousex>537&&mousex<587&&mousey>228&&mousey<271&&on==1)
        {

            if(key!=10)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=10;

            pointer_x=537;
            pointer_y=228;
            pbx=587;
            pby=268;
            plx=558;
            ply=245;
            paste_string="/";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(but==1&&key1!=10)
            {
                temp1=atof(input);
                if(div==0&&equal==1)
                {
                    div=1;
                    equal=0;

                    gcvt(ans,10,input);
                }
                else if(add==0&&sub==0&&mul==0&&div==0)
                {
                    ans=temp1;
                    div=1;

                }
                else if(add==0&&sub==1&&mul==0&&div==0)
                {
                    sub=0;mul=0;div=1;add=0;
                    ans=ans-temp1;
   
                    gcvt(ans,10,input);
                }
                else if(add==1&&sub==0&&mul==0&&div==0)
                {
                    sub=0;mul=0;div=1;add=0;
                    ans=ans+temp1;
     
                    gcvt(ans,10,input);
                }
                else if(add==0&&sub==0&&mul==1&&div==0)
                {
                    sub=0;add=0;div=1;mul=0;
                    ans=ans*temp1;
                    
                    gcvt(ans,10,input);
                }
                else if(div==1)
                {
                    sub=0;mul=0;add=0;
                    if(temp1==0)
                    {
                    setfillstyle(1,0);
                    bar(51,141,586,169);
                    setcolor(11);
                    input="Divide by zero error";
                    outtextxy(vx-strlen(input)*8+8,vy,input);
                    }
                    else
                    {
                    ans=ans/temp1;
                    gcvt(ans,10,input);  //gcvt  Convert double to ascii string
                    }
                }
                operation=4;
              setfillstyle(1,9);
                bar(330,141,586,169);
                
                setcolor(11);
               
                   outtextxy(vx-strlen(input)*8+8,vy,input);

                for(int k=0;k<count;k++)
                {
                    input[k]='\0';
                }
                count=0;
                setcolor(0);
                temp1=0;
                key1=10;
                delay(200);
             
            }
        }
        else if(mousex>325&&mousex<375&&mousey>271&&mousey<311&&on==1)
        {

            if(key!=11)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=11;

            pointer_x=325;
            pointer_y=271;
            pbx=375;
            pby=311;
            plx=348;
            ply=288;
            paste_string="1";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(but==1&&key1!=11&&strlen(input)<9)
            {
               
              setfillstyle(1,9);
                bar(330,141,586,169);;
                setcolor(11);
                strcat(input,paste_string);
                outtextxy(vx-count*8,vy,input);
                count++;
                setcolor(0);
                key1=11;
                delay(200);
                key1=0;
            }

        }
        else if(mousex>378&&mousex<428&&mousey>271&&mousey<311&&on==1)
        {

            if(key!=12)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=12;

            pointer_x=378;
            pointer_y=271;
            pbx=428;
            pby=311;
            plx=401;
            ply=288;
            paste_string="2";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(but==1&&key1!=12)
            {
                
              setfillstyle(1,9);
                bar(330,141,586,169);
                setcolor(11);
                strcat(input,paste_string);
                outtextxy(vx-count*8,vy,input);
                count++;
                setcolor(0);
                key1=12;
                delay(200);
                key1=0;
            }

        }
        else if(mousex>431&&mousex<481&&mousey>271&mousey<311&&on==1)
        {

            if(key!=13)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=13;

            pointer_x=431;
            pointer_y=271;
            pbx=481;
            pby=311;
            plx=454;
            ply=288;
            paste_string="3";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(but==1&&key1!=13&&strlen(input)<9)
            {
               
              setfillstyle(1,9);
                bar(330,141,586,169);
                setcolor(11);
                strcat(input,paste_string);
                outtextxy(vx-count*8,vy,input);
                count++;
                setcolor(0);
                key1=13;
                delay(200);
                key1=0;             // to use again the functionality of that button
            }

        }
        else if(mousex>484&&mousex<534&&mousey>271&&mousey<311&&on==1)
        {

            if(key!=14)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=14;

            pointer_x=484;
            pointer_y=271;
            pbx=534;
            pby=311;
            plx=505;
            ply=288;
            paste_string="+";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(but==1&&key1!=14)
            {
                temp1=atof(input);
                if(add==0&&equal==1)
                {
                    add=1;
                    equal=0;

                }
                else if(add==0&&sub==0&&mul==0&&div==0)
                {
                    ans=temp1;
                    add=1;
 
                }
                else if(add==0&&sub==1&&mul==0&&div==0)
                {
                    sub=0;mul=0;div=0;add=1;
                    ans=ans-temp1;
   
                }
                else if(add==0&&sub==0&&mul==1&&div==0)
                {
                    sub=0;mul=0;div=0;add=1;
                    ans=ans*temp1;
      
                }
                else if(add==0&&sub==0&&mul==0&&div==1)
                {
                    sub=0;mul=0;div=0;add=1;
                    ans=ans/temp1;
        
                }
                else if(add==1)
                {
                    sub=0;mul=0;div=0;
                    ans=ans+temp1;
         
                }
                operation=1;
               setfillstyle(1,9);
                bar(330,141,586,169);
                setcolor(11);
                gcvt(ans,10,input);
                if(strlen(input)>9)
                    ob.strcut(input);
          
                if(strlen(input)<=9)
                outtextxy(vx-strlen(input)*8+8,vy,input);
                
                for(int k=0;k<count;k++)
                {
                    input[k]='\0';
                }
                count=0;
                setcolor(0);
                temp1=0;
                key1=14;
                delay(200);
                
            }

        }
        else if(mousex>537&&mousex<587&&mousey>271&&mousey<311&&on==1)
        {

            if(key!=15)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=15;

            pointer_x=537;
            pointer_y=271;
            pbx=587;
            pby=311;
            plx=558;
            ply=288;
            paste_string="-";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(but==1&&key1!=15)
            {
                temp1=atof(input);
                if(sub==0&&equal==1)
                {
                    sub=1;
                    equal=0;
                   
                }
                else if(sub==0&&add==0&&mul==0&&div==0)
                {
                    ans=temp1;
                    sub=1;

                }
                else if(sub==0&&add==1&&mul==0&&div==0)
                {
                    add=0;mul=0;div=0;sub=1;
                    ans=ans+temp1;
 
                }
                else if(add==0&&sub==0&&mul==1&&div==0)
                {
                    sub=1;mul=0;div=0;add=0;
                    ans=ans*temp1;
   
                }
                else if(add==0&&sub==0&&mul==0&&div==1)
                {
                    sub=0;mul=0;div=1;add=0;
                    ans=ans/temp1;
                }
                else if(sub==1)
                {
                    add=0;mul=0;div=0;
                    ans=ans-temp1;
      
                }
                operation=2;
               setfillstyle(1,9);
                bar(330,141,586,169);
                setcolor(11);
                gcvt(ans,10,input);
                if(strlen(input)>9)
                    ob.strcut(input);
         
                if(strlen(input)<=9)
                outtextxy(vx-strlen(input)*8+8,vy,input);
                
                for(int k=0;k<count;k++)
                {
                    input[k]='\0';
                }
                count=0;
                setcolor(0);
                temp1=0;
                key1=14;
                delay(200);
             
            }

        }
        else if(mousex>378&&mousex<428&&mousey>314&&mousey<354&&on==1)
        {

            if(key!=16)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=16;

            pointer_x=378;
            pointer_y=314;
            pbx=428;
            pby=354;
            plx=401;
            ply=329;
            paste_string="0";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(but==1&&key1!=16)
            {
              
              setfillstyle(1,9);
                bar(330,141,586,169);
                setcolor(11);
                strcat(input,paste_string);
                outtextxy(vx-count*8,vy,input);
                count++;
                setcolor(0);
                key1=16;
                delay(200);
                key1=0;
            }

        }
        else if(mousex>431&&mousex<481&&mousey>314&mousey<354&&on==1)
        {

            if(key!=17)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=17;

             pointer_x=431;
            pointer_y=314;
            pbx=481;
            pby=354;
            plx=445;
            ply=331;
            paste_string=".";
            plx1=0;
            ply1=0;
            paste_string1="";
            }
            if(but==1&&key1!=16)
            {
                
               setfillstyle(1,9);
                bar(330,141,586,169);
                setcolor(11);
                strcat(input,paste_string);

                
                setcolor(0);
                key1=17;
                delay(200);
                key1=0;
            }

        }
        else if(mousex>484&&mousex<534&&mousey>314&&mousey<354&&on==1)
        {

            if(key!=19)
            {
            ob.button(pointer_x,pointer_y,pbx,pby,plx,ply,plx1,ply1,paste_string,paste_string1);
            key=19;

            pointer_x=484;
            pointer_y=314;
            pbx=534;
            pby=354;
            plx=498;
            ply=331;
            paste_string="ANS";
            plx1=0;
            ply1=0;
            paste_string1="";
            }


            if(but==1&&key1!=19)
            {       switch(operation)
                {
                case 1:
                {
                    temp1=atof(input);
                    ans=ans+temp1;
                }break;
                case 2:
                {
                    temp1=atof(input);
                    ans=ans-temp1;
                }break;
                case 3:
                {
                    temp1=atof(input);
                    ans=ans*temp1;
                }break;
                case 4:
                {
                    temp1=atof(input);
                    if(temp1==0)
                    {
                        input="Divide by zero error.";
                    }
                    else
                    {
                        ans=ans/temp1;
                        gcvt(ans,10,input);
                    }
                }break;
                
                }
                equal=1;
               setfillstyle(1,9);
                bar(330,141,586,169);
                setcolor(11);

                if(operation==4)
                outtextxy(vx-strlen(input)*8+8,vy,input);
                else
                {
                gcvt(ans,10,input);
                if(strlen(input)>9)
                    ob.strcut(input);
                outtextxy(vx-strlen(input)*8+8,vy,input);
                }
                for(int k=0;k<count;k++)
                {
                    input[k]='\0';
                }
                operation=0;
                add=0;sub=0;mul=0;div=0;
                setcolor(0);
                temp1=0;
                key1=19;
                delay(200);
               
            }

        }

       
        if(but==2)
            break;


    }
    //getch();
}