#ifndef MAP_ACCESS_9
#define MAP_ACCESS_9

#include "game/map_types.h"

static inline vect3D getCluster(map_struct* m, int i, int j, int k)
{
	if(i<0 || j<0 || k<0 || i>=m->size.x || j>=m->size.y || k>=m->size.z)return (vect3D){0,0,0};
	return (vect3D){(i-i%CLUSTERSIZE)/CLUSTERSIZE,(j-j%CLUSTERSIZE)/CLUSTERSIZE,(k-k%CLUSTERSIZE)/CLUSTERSIZE};
}

// static inline u8* getBlockP(map_struct* m, int i, int j, int k)
// {
	// if(i<0 || j<0 || k<0/* || i>=m->size.x*/ || j>=m->size.y || k>=m->size.z)return &m->superCluster[0][0][0].data[0];
	// vect3D cluster=getCluster(m, i, j, k);
	// i-=cluster.x*CLUSTERSIZE;j-=cluster.y*CLUSTERSIZE;k-=cluster.z*CLUSTERSIZE;
	// cluster.x-=m->offset.x;cluster.y-=m->offset.y;cluster.z-=m->offset.z;
	// if(cluster.x<0 || cluster.y<0 || cluster.z<0 || cluster.x>=32 || cluster.y>=32 || cluster.z>=32)return &m->superCluster[0][0][0].data[0];
	// return &m->superCluster[cluster.x][cluster.y][cluster.z].data[i+j*CLUSTERSIZE+k*CLUSTERSIZE*CLUSTERSIZE];
// }

static inline u8* getBlockPE(map_struct* m, int i, int j, int k)
{
	if(i<0 || j<0 || k<0/* || i>=m->size.x*/ || j>=m->size.y || k>=m->size.z)return &m->superCluster[0][0][0].data[0];
	vect3D cluster=getCluster(m, i, j, k);
	i-=cluster.x*CLUSTERSIZE;j-=cluster.y*CLUSTERSIZE;//k-=cluster.z*CLUSTERSIZE;
	cluster.x-=m->offset.x;cluster.y-=m->offset.y;cluster.z-=m->offset.z;
	if((cluster.x<0 && cluster.y<0) || (cluster.x>=32 && cluster.y<0) || (cluster.x>=32 && cluster.y>=32) || (cluster.x<0 && cluster.y>=32) || cluster.x<-1 || cluster.y<-1 || cluster.x>32 || cluster.y>32 || cluster.z<0 || cluster.z>=32)return &m->superCluster[0][0]->data[0];
	if(cluster.x==-1)return &m->transitionCluster[cluster.y]->data[i+j*CLUSTERSIZE+k*CLUSTERSIZE*CLUSTERSIZE];
	else if(cluster.x==32)return &m->transitionCluster[32+cluster.y]->data[i+j*CLUSTERSIZE+k*CLUSTERSIZE*CLUSTERSIZE];
	else if(cluster.y==-1)return &m->transitionCluster[32*2+cluster.x]->data[i+j*CLUSTERSIZE+k*CLUSTERSIZE*CLUSTERSIZE];
	else if(cluster.y==32)return &m->transitionCluster[32*3+cluster.x]->data[i+j*CLUSTERSIZE+k*CLUSTERSIZE*CLUSTERSIZE];
	return &m->superCluster[cluster.x][cluster.y]->data[i+j*CLUSTERSIZE+k*CLUSTERSIZE*CLUSTERSIZE];
}

static inline u8* getBlockP(map_struct* m, int i, int j, int k)
{
	if(i<0 || j<0 || k<0/* || i>=m->size.x*/ || j>=m->size.y || k>=m->size.z)return &m->superCluster[0][0][0].data[0];
	vect3D cluster=getCluster(m, i, j, k);
	i-=cluster.x*CLUSTERSIZE;j-=cluster.y*CLUSTERSIZE;//k-=cluster.z*CLUSTERSIZE;
	cluster.x-=m->offset.x;cluster.y-=m->offset.y;cluster.z-=m->offset.z;
	if(cluster.x<0 || cluster.y<0 || cluster.z<0 || cluster.x>=32 || cluster.y>=32 || cluster.z>=32)return &m->superCluster[0][0]->data[0];
	return &m->superCluster[cluster.x][cluster.y]->data[i+j*CLUSTERSIZE+k*CLUSTERSIZE*CLUSTERSIZE];
}

static inline bool isLadder(u8 t)
{
	return (t>=LADDERTYPE && t<LADDERTYPE+4);
}

static inline bool isDoor(u8 t)
{
	return (t>=DOORTYPE && t<DOORTYPE+16);
}

static inline bool isOpenDoor(u8 t)
{
	return (t>=DOORTYPE+8 && t<DOORTYPE+16);
}

static inline bool transparent2(map_struct* m, int i, int j, int k, int i2, int j2, int k2)
{
	const u8 t=*getBlockP(m,i2,j2,k2);
	const u8 tt=*getBlockP(m,i,j,k);
	return ((t==0 || t>=WATERTYPE || t==12 || t==13 || isLadder(t) || isDoor(t)) && (!(t==tt || (t>=WATERTYPE && tt>=WATERTYPE))));
}

static inline bool transparent3(map_struct* m, int i, int j, int k, int i2, int j2, int k2)
{
	const u8 t=*getBlockPE(m,i2,j2,k2);
	const u8 tt=*getBlockPE(m,i,j,k);
	return ((t==0 || t>=WATERTYPE || t==12 || t==13 || isLadder(t) || isDoor(t)) && (!(t==tt || (t>=WATERTYPE && tt>=WATERTYPE))));
}

static inline bool solid(u8 type)
{
	return (type && type<WATERTYPE && type!=13 && !isLadder(type) && !isOpenDoor(type));
}

static inline bool block(u8 type)
{
	return (type && type!=13 && !isLadder(type) && !isDoor(type));
}

static inline bool tangible(u8 type)
{
	return (type && type<WATERTYPE);
}

static inline void getLightWC(map_struct* m, int i, int j, int k, u8* light, u8 direction, lightsource_struct* q)
{
	u8 s=((*light)&(1<<7));
	*light=0;
	const u16 d=direction<<12;
	while(q)
	{
		u8 i2=-(i%CLUSTERSIZE)+q->i+8;
		u8 j2=-(j%CLUSTERSIZE)+q->j+8;
		u8 k2=-(k%CLUSTERSIZE)+q->k+8;
		// if(i2>0 && j2>0 && k2>0 && i2<13 && j2<13 && k2<13)
		{
			// *light|=min(((*light)&127)+lightTable[i2*6+j2*6*13+k2*6*13*13+direction],127)&127;
			// *light=min((*light)+lightTable[i2*8+j2*8*16+k2*8*16*16+direction],127);
			*light=min((*light)+lightTable[i2+j2*16+k2*16*16+d],127);
		}
		// NOGBA("t");
		q=q->next;
	}
	(*light)|=s;
		// NOGBA("d");
}

static inline void getLight(map_struct* m, int i, int j, int k, u8* light, u8 direction)
{
	vect3D clusterCoord=getCluster(m,i,j,k);
	lightsource_struct *q=m->superCluster[clusterCoord.x-m->offset.x][clusterCoord.y-m->offset.y]->cluster[clusterCoord.z-m->offset.z].lightList.first;
	getLightWC(m, i, j, k, light, direction, q);
}

static inline u8 getHighest(map_struct* m, int i, int j)
{
	vect3D clusterCoord=getCluster(m,i,j,16);
	i%=CLUSTERSIZE;
	j%=CLUSTERSIZE;
	return m->superCluster[clusterCoord.x-m->offset.x][clusterCoord.y-m->offset.y]->highest[i+j*CLUSTERSIZE];
}

static inline void surface(map_struct* m, int i, int j, int k, u8* light) //A OPTIMISER
{
	const vect3D clusterCoord=getCluster(m,i,j,k);
	const vect3D clusterCoord1=getCluster(m,i-1,j,k);
	const vect3D clusterCoord2=getCluster(m,i+1,j,k);
	const vect3D clusterCoord3=getCluster(m,i,j-1,k);
	const vect3D clusterCoord4=getCluster(m,i,j+1,k);
	if(k>=m->superCluster[clusterCoord.x-m->offset.x][clusterCoord.y-m->offset.y]->highest[(i%CLUSTERSIZE)+(j%CLUSTERSIZE)*CLUSTERSIZE]
	|| k>m->superCluster[clusterCoord1.x-m->offset.x][clusterCoord1.y-m->offset.y]->highest[((i-1)%CLUSTERSIZE)+((j)%CLUSTERSIZE)*CLUSTERSIZE]
	|| k>m->superCluster[clusterCoord2.x-m->offset.x][clusterCoord2.y-m->offset.y]->highest[((i+1)%CLUSTERSIZE)+((j)%CLUSTERSIZE)*CLUSTERSIZE]
	|| k>m->superCluster[clusterCoord3.x-m->offset.x][clusterCoord3.y-m->offset.y]->highest[((i)%CLUSTERSIZE)+((j-1)%CLUSTERSIZE)*CLUSTERSIZE]
	|| k>m->superCluster[clusterCoord4.x-m->offset.x][clusterCoord4.y-m->offset.y]->highest[((i)%CLUSTERSIZE)+((j+1)%CLUSTERSIZE)*CLUSTERSIZE])(*light)|=(1<<7);
}

static inline bool seeThrough(u8 type)
{
	return (!type || type>=WATERTYPE || type==13 || type==12 || isLadder(type) || isOpenDoor(type) || type==10);
}

static inline void surface2(map_struct* m, int i, int j, int k, u8* light) //A OPTIMISER
{
	const vect3D clusterCoord=getCluster(m,i,j,k);
	const clusterColumn_struct *cC=m->superCluster[clusterCoord.x-m->offset.x][clusterCoord.y-m->offset.y];
	i%=CLUSTERSIZE;
	j%=CLUSTERSIZE;
	(*light)=(1<<7);
	u8 l;
	for(l=63;l>k;l--)
	{
		if(!seeThrough(cC->data[(i)+(j)*CLUSTERSIZE+l*CLUSTERSIZE*CLUSTERSIZE])){(*light)=0;return;}
	}
}

#endif
