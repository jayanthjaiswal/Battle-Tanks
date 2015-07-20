void GamePlayScreen(){
			ClearScreen();
     		TerrainGenerator(); 
     		
            
            Tank1Health=1000;
            Tank2Health=1000;
	        n=7;
	        
	        PlayerNumber=1;
			TerrainTexture.Load("Images/Terrain.xpm");
			InputBackground.Load("Images/InputBackground.xpm");
			PowerBMP.Load("Images/Power.xpm");
			AngleBMP.Load("Images/Angle.xpm");
			Fire.Load("Images/Fire.xpm");
			TankBMP1.Load("Images/Tank1.xpm");
			TankBMP2.Load("Images/Tank2.xpm");
			Sky.Load("Images/Sky.xpm");

	GameLoad();

		//check if the bitmap at the ith element of the array is selected. It is then loaded at the jth position on the screen*/
}



/* fuction to generate unique terrain: a special effort made to enforce modularity*/
void TerrainGenerator(){
    srand((unsigned int) time(0));
    int i, j;
    float k;
   
    //TerrainHeight[0]=(float) (rand()%(int) ((Height*2/3) - (Height/2))) + (Height/2);
    TerrainHeight[0] = Height*4/6;
    for(j=1;j<(5*Width);j++){  //horizontal axis divided into 100*Width parts
        TerrainHeight[j] = TerrainHeight[j-1] - ((float)(rand()%9))/80 + (float)8/160 - .03;
        if(TerrainHeight[j]<(Height/3)){TerrainHeight[j]=(Height/3);} //terrain is randomly generated
        if(TerrainHeight[j]>(Height*5/6)){TerrainHeight[j]=(Height*5/6);}//bounday conditions
        } //y coordinates stored in the array "height"
    for(j=(5*Width);j<(10*Width);j++){  //horizontal axis divided into 100*Width parts
        TerrainHeight[j] = TerrainHeight[j-1] + ((float)(rand()%9))/80 - (float)8/160 + .03;
        if(TerrainHeight[j]<(Height/3)){TerrainHeight[j]=(Height/3);} //terrain is randomly generated
        if(TerrainHeight[j]>(Height*5/6)){TerrainHeight[j]=(Height*5/6);}//bounday conditions
        } //y coordinates stored in the array "height"
 
}
