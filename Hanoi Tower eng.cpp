#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <math.h>

using namespace std;

class disco                               //the "disco" class has all the elements that
{                                       //defines every disk in the game: the size , the vertical position and the
	public:                           //rod where is every disk;
		int rad;
		int col;
		int pos;
};

void wincheck(disco*torrepp,int*numdispp,int*nompp,int*jpp,float*nmmpp)//checks if the game was won and; 
{                                                                  //print a message to the player;
	int u=0,i;                                             
	for(i=0;i<*numdispp;i++)
	{
		if((*(torrepp+i)).col==3)
		{
			u++;
		}
	}
	if(u==*numdispp)
	{
		if(u==(*nmmpp))
		{
			cout<<"\n\n\n"<<"-----------------------------------------------------------------------------"<<'\n';
	    	cout<<"                                WELL DONE!!!"<<'\n';
	    	cout<<'\n'<<"You made it in "<<*nompp<<" movements, which is the minimum possible number of"<<'\n';
			cout<<"               moves to solve the game!!!"; 
	    	cout<<"\n\n\n"<<"-----------------------------------------------------------------------------"<<'\n';
		}
		else
		{
			cout<<"\n\n\n"<<"-----------------------------------------------------------------------------"<<'\n';
		    cout<<"                                WELL DONE!!!"<<'\n';
		    cout<<'\n'<<"               But you can do it with less movements!";
		    cout<<'\n'<<"You finished the game in "<<*nompp<<" movements, when you could make it in "<<*nmmpp<<'\n'; 
		    cout<<"\n\n\n"<<"-----------------------------------------------------------------------------"<<'\n';
		}
		*jpp=1;
	}
}

void transf(int*dtmp,int*mtpp,disco*torrepp,int*numdispp,int*nompp) //once the movement was validated this; 
{                                                                  //algorithm does the data changes in the; 
	int coldef[*numdispp],i,j=0,ind=0;                             //objects of the "disco" class;
	for(i=0;i<*numdispp;i++)                                       
	{
		coldef[i]=0;
	}
	for(i=0;i<*numdispp;i++)
	{
		if(((*(torrepp+i)).col)==(*mtpp))
		{
			coldef[((*(torrepp+i)).pos)-1]=((*(torrepp+i)).rad);
		}
	}
	if(coldef[(*numdispp)-1]==0)
	{
		ind=(*numdispp);
	}
	else
	{
		for(i=0;i<*numdispp;i++)
		{
			if(coldef[i]!=0&&j==0)
			{
				ind=i;
				j=1;
			}
		}
	}
	((*(torrepp+(*dtmp)-1)).col)=(*mtpp);
	((*(torrepp+(*dtmp)-1)).pos)=ind;
	*nompp+=1;
}

void valtest2(disco*torrepp,int*mtpp,int*dtmp,int*numdispp,int*k0,int*k1)//checks if the chosen disk is already;
{                                                                 //in the chosen position;
	int i,j,ind,coldef[*numdispp];                                 //then, checks if the chosen position has;
	while(*k1==0)                                                  //a bigger disk than the one you are trying to move;
	{
		ind=0;
		j=0;
		for(i=0;i<*numdispp;i++)
	    {
		    coldef[i]=0;
	    }
		for(i=0;i<*numdispp;i++)
    	{
    		if(((*(torrepp+i)).col)==(*mtpp))
    		{
	    		coldef[((*(torrepp+i)).pos)-1]=((*(torrepp+i)).rad);
	    	}
     	}
    	for(i=0;i<*numdispp;i++)
    	{
	    	if(coldef[i]!=0&&j!=1)
	    	{
	    		ind=i;
	    		j=1;
	    	}
    	}
	 	if((*mtpp)==(((*(torrepp+(*dtmp)-1)).col)))
		{
			cout<<"It's already there, please define another position:  ";
			cin>>*mtpp;
			*k0=0;
		}
		else
		{
			if(ind==0&&coldef[0]==0)
			{
				*k1=1;
			}
			else
			{
				if(coldef[ind]<((*(torrepp+(*dtmp)-1)).rad))
				{
					cout<<"Not allowed, please define another position:  ";
					cin>>*mtpp;
					*k0=0;
				}
				else
				{
					*k1=1;
				}
			}
		}
	}
}

void valtest1b(int*mtpp,int*k0,int*k1)                     //checks if the chosen rod is more than 3 or less
{                                                         // than 1;
	while(*k0==0)
	{
		if(*mtpp<=0||*mtpp>3)
		{
			cout<<"Out of range, please define another position: ";
			cin>>*mtpp;
			*k1=0;
		}
		else
		{
			*k0=1;
		}
	}
}

void valtest1(int*dtmp,disco*torrepp,int*numdispp,int*k0,int*k1,int*k2)      //Checks if the chosen disk is under;
{                                                                            //another disk.
	int i,j=0;                                              
	while(*k2==0)
	{
		j=0;
	    for(i=0;i<*numdispp;i++)
	    {
		    if((*(torrepp+i)).col==(*(torrepp+(*dtmp)-1)).col&&(i+1)!=(*dtmp)&&j==0)
		    {
		    	if((*(torrepp+i)).pos<(*(torrepp+(*dtmp)-1)).pos)
		    	{
		    		cout<<"Not allowed, please choose another disk: ";
		    		cin>>(*dtmp);
		    		j=1;
		    		*k0=0;
		    		*k1=0;
		    	}
		    	else
		    	{
		    		*k2=1;
		    	}
		    }
		    else
		    {
		    	if(i==(*numdispp)-1&&j==0)
		    	{
		    		*k2=1;
		    	}
		    }
	    }
	}
}

void valtest0b(int*dtmp,disco*torrepp,int*numdispp,int*k0,int*k1,int*k2) //This algorithm checks if the chosen disk;
{                                                   //cannot be moved of its position;
	int vfp[3][2],i,j;                            
	while(*k1==0)                                   //This could happen if the chosen disk is bigger;
	{                                             // than the disks allocated in the other two rods;
		int radx=0,radn=1;                       
	    for(i=0;i<3;i++)                          
    	{
	    	vfp[i][0]=*numdispp;
    		vfp[i][1]=0;
    	}
    	for(i=0;i<*numdispp;i++)
    	{
    		if((*(torrepp+i)).col==1&&((*(torrepp+i)).pos)<=vfp[0][0])
	    	{
	    		vfp[0][0]=((*(torrepp+i)).pos);
	    		vfp[0][1]=((*(torrepp+i)).rad);
            }
    		if((*(torrepp+i)).col==2&&((*(torrepp+i)).pos)<=vfp[1][0])
    		{
    			vfp[1][0]=((*(torrepp+i)).pos);
     			vfp[1][1]=((*(torrepp+i)).rad);
	        }
	    	if((*(torrepp+i)).col==3&&((*(torrepp+i)).pos)<=vfp[2][0])
	    	{
	    		vfp[2][0]=((*(torrepp+i)).pos);
	    		vfp[2][1]=((*(torrepp+i)).rad);
	    	}
        }
    	for(i=0;i<3;i++)
    	{
    		if(vfp[i][1]==0)
    		{
    			radn=0;
    		}
    		if(vfp[i][1]>radx)
    		{
    			radx=vfp[i][1];
    		}
        }
        if(radx==(*dtmp))
        {
        	if(radn==1)
			{
				cout<<"Not allowed, please choose another disk: ";
        	    cin>>*dtmp;
        	    *k0=0;
        	    *k2=0;
			}
			else
			{
				*k1=1;
			}
        }
        else
        {
        	*k1=1;
        }
	}
}

void valtest0(int*dtmp,int*numdispp,int*k0,int*k1,int*k2) //Verifies if the player chooses a disk that no exists;
{                                                                                           
	while(*k0==0)                                    
	{
		if((*dtmp>*numdispp)||(*dtmp<=0))
		{
			cout<<'\n'<<"Out of range, please choose another disk: ";
			cin>>*dtmp;
			*k1=0;
			*k2=0;
		}
		else
		{
			*k0=1;
		}
	}
}

void player(disco*torrep,int*numdisp,int*nomp,int*jp,float*nmmp)//function to solve all the player movements;
{
	int dtm=0,mtp=0,p,k0=0,k1=0,k2=0;
		wincheck(torrep,numdisp,nomp,jp,nmmp);//Checks if the game wasn't won;
		if(*jp==0)     //If the game wasn't won ask the player for a new movement;
		{
			cout<<'\n'<<"Disk to move?:  ";             //Set the disk to move;
		    cin>>dtm;
		    while(k0==0||k1==0||k2==0)                        //checks again all the possibilities of ;
		    {                                                 //wrong disk election if, in one of the checkings,;
		    	valtest0(&dtm,numdisp,&k0,&k1,&k2);           //the player had to change the elected disk;
		        valtest0b(&dtm,torrep,numdisp,&k0,&k1,&k2);
		        valtest1(&dtm,torrep,numdisp,&k0,&k1,&k2);
		    }
		    k0=0;
		    k1=0;
		    cout<<"What position?: ";             //set the new position of the disk;
		    cin>>mtp;
		    while(k0==0||k1==0)                        //this loop checks again all the possibilities of wrong;
			{                                          //rod election if, in one of the checkings, the player;
				valtest1b(&mtp,&k0,&k1);               //had to change the elected rod;
		        valtest2(torrep,&mtp,&dtm,numdisp,&k0,&k1);
			}
		    transf(&dtm,&mtp,torrep,numdisp,nomp);
		}
}

void espmatload(int*espmatp,int*matp,int*numdispp)//algorithm to set the spaces between rodes; 
{                                                 // and then save the data in a matrix;
	int base=(*numdispp)+3,i;
	for(i=0;i<*numdispp;i++)
	{
		*(espmatp+(i*3))=0;
		*(espmatp+(i*3)+1)=0;
		*(espmatp+(i*3)+2)=0;
	}
	for(i=0;i<*numdispp;i++)
	{
		if((*(matp+(i*3)))==0)
		{
			*(espmatp+(i*3))=base;
		}
		else
		{
			*(espmatp+(i*3))=base-((*(matp+(i*3))-1));
		}
		if((*(matp+(i*3)))==0&&(*(matp+(i*3)+1))==0)
		{
			*(espmatp+(i*3)+1)=base*2;
		}
		else
		{
			if((*(matp+(i*3)))!=0&&(*(matp+(i*3)+1))!=0)
			{
				*(espmatp+(i*3)+1)=((base*2))-((*(matp+(i*3)))-1)-((*(matp+(i*3)+1))-1);
			}
			else
			{
				*(espmatp+(i*3)+1)=((base*2)-1)-((*(matp+(i*3)))-1)-((*(matp+(i*3)+1))-1);
			}
		}
		if((*(matp+(i*3)+1))!=0&&(*(matp+(i*3)+2)==0))
		{
			*(espmatp+(i*3)+2)=((base*2)-1)-((*(matp+(i*3)+1))-1)-((*(matp+(i*3)+2))-1);
		}
		else
		{
			if((*(matp+(i*3)+1))!=0&&(*(matp+(i*3)+2)!=0))
			{
				*(espmatp+(i*3)+2)=((base*2))-((*(matp+(i*3)+1))-1)-((*(matp+(i*3)+2))-1);
			}
			else
			{
				if((*(matp+(i*3)))!=0&&(*(matp+(i*3)+1))==0&&(*(matp+(i*3)+2)!=0))
				{
					*(espmatp+(i*3)+2)=((base*2)-1)-((*(matp+(i*3)+1))-1)-((*(matp+(i*3)+2))-1);
				}
				else
				{
					if((*(matp+(i*3)))==0&&(*(matp+(i*3)+1))==0&&(*(matp+(i*3)+2)!=0))
					{
						*(espmatp+(i*3)+2)=((base*2)-1)-((*(matp+(i*3)+1))-1)-((*(matp+(i*3)+2))-1);
					}
					else
					{
						*(espmatp+(i*3)+2)=((base*2)-2)-((*(matp+(i*3)+1))-1)-((*(matp+(i*3)+2))-1);
					}
				}
			}
		}
	}
}

void carmat(disco*torrepp,int*numdispp,int*matp)//matrix data load of the disks positions and the holes;
{                                               //to easily check later the occupied spaces and the free spaces; 
	int i,j,k;                                  //in the three rods;
	for(i=0;i<(*numdispp)*3;i+=3)
	{
		*(matp+i)=0;
		*(matp+i+1)=0;
		*(matp+i+2)=0;
	}
	for(i=0;i<*numdispp;i++)
	{
		for(j=0;j<3;j++)
		{
			for(k=0;k<*numdispp;k++)
			{
				if(((*(torrepp+k)).pos)==(i+1)&&((*(torrepp+k)).col)==(j+1))
			    {   
				    (*(matp+(3*i)+j))=((*(torrepp+k)).rad);
			    }
			}
		}
	}
}

void draw(disco*torrep,int*numdisp)//Screen output of the game based in the actual data of the disks position;
{
	int i,j,k,mat[*numdisp][3],espmat[*numdisp][3];
	carmat(torrep,numdisp,&mat[0][0]);//matrix data load;
	espmatload(&espmat[0][0],&mat[0][0],numdisp);//call a function to set the spaces between rods;
	for(i=0;i<*numdisp;i++)//This loop prints the actual state of the game;
	{
		if(i==0)
		{
			printf("%*c%*c%*c\n",*numdisp+3,179,(*numdisp+3)*2,
			179,(*numdisp+3)*2,179);
		}
		for(j=0;j<3;j++)
		{
			if(mat[i][j]==0)
			{
				printf("%*c",espmat[i][j],179);
			}
			else
			{
				printf("%*c",espmat[i][j],176);
				for(k=0;k<(mat[i][j]-1)*2;k++)
				{
					printf("%c",176);
				}
			}
		}
		cout<<'\n';
	}
}

int main()
{
	int numdis=0,i,nom=0,j=0;
	float nmm=0;
	cout<<"\n\n"<<"                "<<"<< Hanoi Tower Game >>"<<"    "<<'\n';
	cout<<"                     "<<"SAH"<<"   ";
	cout<<"  "<<"2014"<<"\n\n\n\n";
	cout<<'\n'<<"Objective:"<<'\n'<<"Put all the disks in the left column in descending order"<<'\n';
	cout<<"General Rules: "<<'\n'<<"1 - You can move only one disk in each movement"<<'\n';
	cout<<"2 - You cannot put a disk on one that is smaller"<<'\n';
	cout<<"   than the disk you're trying to move' "<<"\n\n\n";
	cout<<"Set the number of disk :  "<<"\n \n";
	cin>>numdis;
	while(j==0)
	{                                      //This loop checks that the number of disks isn't;
		if(numdis>12||numdis<3)                      //more than 12 or less than 3, also, it saves the minimun;   
		{                                            //number of movements necesary to solve the problem;
			cout<<"Not allowed, please set again the number of disks: ";
			cin>>numdis;
		}
		else
		{
			j=1;
			nmm=(pow(2,numdis))-1;
		}
	}
	cout<<"\n \n";
	disco torre[numdis];
	for(i=0;i<numdis;i++)//this loop puts all the disks in descending order and in the first column;
	{                     //saving the data in the "disco" class;
		torre[i].rad=i+1;
		torre[i].col=1;
		torre[i].pos=i+1;
	}
	j=0;
	while(j==0) //Here starts the game;
	{
		draw(&(torre[0]),&(numdis));//Call a function to draw the tower in the screen;
		player(&(torre[0]),&numdis,&nom,&j,&nmm);//player movements function;
	}
	cout<<"\n\n\n\n";
	system("PAUSE");
	return 0;
}
