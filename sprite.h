#ifndef SPRITE_H
#define SPRITE_H
//=====================================================================
//Sprite
//=====================================================================
//Note: This is used to hold the images of ppm files
//      Example how to use:
//        Sprite var1;
//        ... 
//        In initOpengl(){ //When Initiaizing Stuff
//          ...
//          var1.insert(image.ppm, row, column);
//          ...
//        }
//        //In Rendering Function
//          ...
//          var1.drawTile(x,y)
//          //This will draw on a coordinates of the tile
//
//For this to work properly, the image sheet must have sprite Evenly Split
//between each other
//---------------------------------------------------------------------
class Sprite{
  //Global Access-------------------------------------------------------
  private:
    const char *imageName;
    int row;
    int column;
    float imageHeight;
    float imageWidth;
    float clipX;
    float clipY;

    Ppmimage *image;
    GLuint texture;

  //Functions-----------------------------------------------------------
  public:
    //Setting Up 
    Sprite();
    void insert(const char *filename, int x, int y);
    void setFile(const char *filename);
    void initSprite();
    void setClip(int x, int y);

    //Outter Functions
    void drawFont(int atSet);
    void drawTile(int row, int column);
    void replaceTexture(GLuint take);
    GLuint textureBox();

    //Function Aid
    unsigned char *buildAlphaData2(Ppmimage *img);
};
//====================================================================
//
//=====================================================================
//Setting Up
//=====================================================================
//    -- This sections includes all functions that changes and initialize
//       the variables in the sprite class.

//Default Contructor
Sprite::Sprite(){
  //when making a Sprite Variable, sets all variables within to 0 or NULL
  imageName = NULL;
  texture = 0;
  clipX = 0; 
  clipY = 0;
  setClip(0, 0);
  imageHeight = 0;
  imageWidth = 0;
}

void Sprite::insert(const char *filename, int x, int y){
  //Gets the number of images place in a row and column x , y
  //then gets the name of the image file
  setFile(filename);
  initSprite(); 
  setClip(x, y); 
}

void Sprite::setFile(const char *filename){
  //Change the imageName to ppm file. imageName is used in the initSprite();
  imageName = filename; 
}

void Sprite::setClip(int x, int y){
  //User defined row and column. The images must evenly split apart from each
  //other. ClipX and ClipY determines where to cut parts in the image.
  row = x; column = y; 
  std::cout << "What is (x,y): (" << row << "," << column << ")\n";
  if(x > 0) clipX = (float)1/row;
  std::cout << "give me CLIPX: " << clipX << std::endl;
  if(y > 0) clipY = (float)1/column;
  std::cout << "give me CLIPY: " << clipY << std::endl;
}

void Sprite::initSprite(){
  //Get an image in input inside the texure
  image = ppm6GetImage(imageName);
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  unsigned char *silhouetteData = buildAlphaData2(image);
  imageWidth  = image->width;
  imageHeight = image->height;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
  delete [] silhouetteData;
}

void Sprite::replaceTexture(GLuint take){
  //It replaces the texture with the texture it got
  //... but this function is not well defined yet
  texture = take;
}
//=====================================================================
//Outter Functions
//=====================================================================
//  These are functions that are use to call drawing events using the variables
//  within this class. Also, giving out this class information

GLuint Sprite::textureBox(){
  //Gives out the texture data/value
  return texture;
}


//This Draws a tile base on row number and column number
//example:
//     1 2 3 4
//   1 # # # #
//   2 # # # #
//   3 # # # #
void Sprite::drawTile(int row, int column){
  //Need to add a safety...
  int atX = row; int atY = column;

  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture);
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_LESS, 1.0f);
  glColor4ub(255,255,255,255);
  glBegin(GL_QUADS);
  float w = imageWidth/32;
  float h = imageHeight/32;

  glTexCoord2f(atX*clipX        , (atY*clipY)+clipY) ; glVertex2i(-w,-h);
  glTexCoord2f(atX*clipX        ,  atY*clipY)        ; glVertex2i(-w,h);
  glTexCoord2f((atX*clipX)+clipX,  atY*clipY)        ; glVertex2i(w,h);
  glTexCoord2f((atX*clipX)+clipX, (atY*clipY)+clipY) ; glVertex2i(w,-h);

  glEnd(); glPopMatrix();
  glDisable(GL_ALPHA_TEST);
}

//This Draws a tile base on line # base on below example
// 1  2  3  4  5  6  7
// 8  9  10 11 12 13 14
//
void Sprite::drawFont(int atSet){     int atX = atSet, atY = 0;         
  atX = atSet % row;
  atY = (int)(atSet/row);

  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture);
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_LESS, 1.0f);
  glColor4ub(255,255,255,255);
  glBegin(GL_QUADS);
  float w = imageWidth/32;
  float h = imageHeight/32;

  glTexCoord2f(atX*clipX        , (atY*clipY)+clipY) ; glVertex2i(-w,-h);
  glTexCoord2f(atX*clipX        ,  atY*clipY)        ; glVertex2i(-w,h);
  glTexCoord2f((atX*clipX)+clipX,  atY*clipY)        ; glVertex2i(w,h);
  glTexCoord2f((atX*clipX)+clipX, (atY*clipY)+clipY) ; glVertex2i(w,-h);

  glEnd(); glPopMatrix();

  glDisable(GL_ALPHA_TEST);
}

//=====================================================================
//Function Aid
//=====================================================================
//Just A helper Function for the init() function in this group. 
//This gets the image convert them to computer readable bytes
//
unsigned char *Sprite::buildAlphaData2(Ppmimage *img){
  //add 4th component to RGB stream...
  int a,b,c;
  unsigned char *newdata, *ptr;
  unsigned char *data = (unsigned char *)img->data;
  //newdata = (unsigned char *)malloc(img->width * img->height * 4);
  newdata = new unsigned char[img->width * img->height * 4];
  ptr = newdata;
  for (int i=0; i<img->width * img->height * 3; i+=3) {
    a = *(data+0);
    b = *(data+1);
    c = *(data+2);
    *(ptr+0) = a;
    *(ptr+1) = b;
    *(ptr+2) = c;
    //get the alpha value
    *(ptr+3) = (a|b|c);
    ptr += 4;
    data += 3;
  }
  return newdata;
}
#endif