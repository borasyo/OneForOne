xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 12;
 -3.15014;-4.04028;3.12461;,
 3.70524;-4.04028;3.18444;,
 3.70524;2.81535;3.18444;,
 -3.15014;2.81535;3.12461;,
 -4.15046;-0.80520;3.28470;,
 0.20384;-0.80520;3.32270;,
 0.20384;3.54926;3.32270;,
 -4.15046;3.54926;3.28470;,
 1.14606;-3.85340;3.33092;,
 4.26346;-3.85340;3.35812;,
 4.26346;-0.73590;3.35812;,
 1.14606;-0.73590;3.33092;;
 
 12;
 3;0,1,2;,
 3;0,2,3;,
 3;0,3,2;,
 3;0,2,1;,
 3;4,5,6;,
 3;4,6,7;,
 3;4,7,6;,
 3;4,6,5;,
 3;8,9,10;,
 3;8,10,11;,
 3;8,11,10;,
 3;8,10,9;;
 
 MeshMaterialList {
  1;
  12;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;1.000000;1.000000;;
   TextureFilename {
    "data\\TEXTURE\\BeamMagic.png";
   }
  }
 }
 MeshNormals {
  6;
  -0.008727;0.000000;0.999962;,
  -0.008726;0.000000;0.999962;,
  -0.008727;0.000000;0.999962;,
  0.008727;0.000000;-0.999962;,
  0.008726;0.000000;-0.999962;,
  0.008727;0.000000;-0.999962;;
  12;
  3;0,0,0;,
  3;0,0,0;,
  3;3,3,3;,
  3;3,3,3;,
  3;1,1,1;,
  3;1,1,1;,
  3;4,4,4;,
  3;4,4,4;,
  3;2,2,2;,
  3;2,2,2;,
  3;5,5,5;,
  3;5,5,5;;
 }
 MeshTextureCoords {
  12;
  0.585470;0.594870;,
  0.004300;0.594870;,
  0.004300;0.013710;,
  0.585470;0.013710;,
  0.958440;0.364320;,
  0.608280;0.364320;,
  0.608280;0.014160;,
  0.958440;0.014160;,
  0.884580;0.624700;,
  0.664020;0.624700;,
  0.664020;0.404140;,
  0.884580;0.404140;;
 }
}
