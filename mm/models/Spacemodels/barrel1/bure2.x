xof 0302txt 0032
Header {
 1;
 0;
 1;
}
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

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template FrameTransformMatrix {
 <F6F23F41-7686-11cf-8F52-0040333594A3>
 Matrix4x4 frameMatrix;
}

template Frame {
 <3D82AB46-62DA-11cf-AB39-0020AF71E433>
 [...]
}
template FloatKeys {
 <10DD46A9-775B-11cf-8F52-0040333594A3>
 DWORD nValues;
 array FLOAT values[nValues];
}

template TimedFloatKeys {
 <F406B180-7B3B-11cf-8F52-0040333594A3>
 DWORD time;
 FloatKeys tfkeys;
}

template AnimationKey {
 <10DD46A8-775B-11cf-8F52-0040333594A3>
 DWORD keyType;
 DWORD nKeys;
 array TimedFloatKeys keys[nKeys];
}

template AnimationOptions {
 <E2BF56C0-840F-11cf-8F52-0040333594A3>
 DWORD openclosed;
 DWORD positionquality;
}

template Animation {
 <3D82AB4F-62DA-11cf-AB39-0020AF71E433>
 [...]
}

template AnimationSet {
 <3D82AB50-62DA-11cf-AB39-0020AF71E433>
 [Animation]
}

template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}

template VertexDuplicationIndices {
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}

template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array FLOAT weights[nWeights];
 Matrix4x4 matrixOffset;
}
Frame MDL-cylind {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,2.162703,1.000000;;
 }
Mesh MSH-cylind {
 332;
-1.533000;0.000000;-2.000000;,
-1.305229;1.305229;-1.066871;,
-1.845873;0.000000;-1.066871;,
-1.083995;1.083995;-2.000000;,
-1.845873;0.000000;-0.933129;,
-1.080234;1.080234;-0.250073;,
-1.527681;0.000000;-0.250073;,
-1.305229;1.305229;-0.933129;,
-1.527681;0.000000;0.250073;,
-1.261956;1.261956;0.932084;,
-1.784675;0.000000;0.932084;,
-1.080234;1.080234;0.250073;,
-1.784675;0.000000;1.067916;,
-1.083995;1.083995;2.000000;,
-1.533000;0.000000;2.000000;,
-1.261956;1.261956;1.067916;,
-1.083995;1.083995;-2.000000;,
0.000000;1.845873;-1.066871;,
-1.305229;1.305229;-1.066871;,
0.000000;1.533000;-2.000000;,
-1.305229;1.305229;-0.933129;,
0.000000;1.527681;-0.250073;,
-1.080234;1.080234;-0.250073;,
0.000000;1.845873;-0.933129;,
-1.080234;1.080234;0.250073;,
0.000000;1.784675;0.932084;,
-1.261956;1.261956;0.932084;,
0.000000;1.527681;0.250073;,
-1.261956;1.261956;1.067916;,
0.000000;1.533000;2.000000;,
-1.083995;1.083995;2.000000;,
0.000000;1.784675;1.067916;,
0.000000;1.533000;-2.000000;,
1.305229;1.305229;-1.066871;,
0.000000;1.845873;-1.066871;,
1.083995;1.083995;-2.000000;,
0.000000;1.845873;-0.933129;,
1.080234;1.080234;-0.250073;,
0.000000;1.527681;-0.250073;,
1.305229;1.305229;-0.933129;,
0.000000;1.527681;0.250073;,
1.261956;1.261956;0.932084;,
0.000000;1.784675;0.932084;,
1.080234;1.080234;0.250073;,
0.000000;1.784675;1.067916;,
1.083995;1.083995;2.000000;,
0.000000;1.533000;2.000000;,
1.261956;1.261956;1.067916;,
1.083995;1.083995;-2.000000;,
1.845873;0.000000;-1.066871;,
1.305229;1.305229;-1.066871;,
1.533000;0.000000;-2.000000;,
1.305229;1.305229;-0.933129;,
1.527681;0.000000;-0.250073;,
1.080234;1.080234;-0.250073;,
1.845873;0.000000;-0.933129;,
1.080234;1.080234;0.250073;,
1.784675;0.000000;0.932084;,
1.261956;1.261956;0.932084;,
1.527681;0.000000;0.250073;,
1.261956;1.261956;1.067916;,
1.533000;0.000000;2.000000;,
1.083995;1.083995;2.000000;,
1.784675;0.000000;1.067916;,
1.533000;0.000000;-2.000000;,
1.305229;-1.305229;-1.066871;,
1.845873;0.000000;-1.066871;,
1.083995;-1.083995;-2.000000;,
1.845873;0.000000;-0.933129;,
1.080234;-1.080234;-0.250073;,
1.527681;0.000000;-0.250073;,
1.305229;-1.305229;-0.933129;,
1.527681;0.000000;0.250073;,
1.261956;-1.261956;0.932084;,
1.784675;0.000000;0.932084;,
1.080234;-1.080234;0.250073;,
1.784675;0.000000;1.067916;,
1.083995;-1.083995;2.000000;,
1.533000;0.000000;2.000000;,
1.261956;-1.261956;1.067916;,
1.083995;-1.083995;-2.000000;,
0.000000;-1.845873;-1.066871;,
1.305229;-1.305229;-1.066871;,
0.000000;-1.533000;-2.000000;,
1.305229;-1.305229;-0.933129;,
0.000000;-1.527681;-0.250073;,
1.080234;-1.080234;-0.250073;,
0.000000;-1.845873;-0.933129;,
1.080234;-1.080234;0.250073;,
0.000000;-1.784675;0.932084;,
1.261956;-1.261956;0.932084;,
0.000000;-1.527681;0.250073;,
1.261956;-1.261956;1.067916;,
0.000000;-1.533000;2.000000;,
1.083995;-1.083995;2.000000;,
0.000000;-1.784675;1.067916;,
0.000000;-1.533000;-2.000000;,
-1.305229;-1.305229;-1.066871;,
0.000000;-1.845873;-1.066871;,
-1.083995;-1.083995;-2.000000;,
0.000000;-1.845873;-0.933129;,
-1.080234;-1.080234;-0.250073;,
0.000000;-1.527681;-0.250073;,
-1.305229;-1.305229;-0.933129;,
0.000000;-1.527681;0.250073;,
-1.261956;-1.261956;0.932084;,
0.000000;-1.784675;0.932084;,
-1.080234;-1.080234;0.250073;,
0.000000;-1.784675;1.067916;,
-1.083995;-1.083995;2.000000;,
0.000000;-1.533000;2.000000;,
-1.261956;-1.261956;1.067916;,
-1.083995;-1.083995;-2.000000;,
-1.845873;0.000000;-1.066871;,
-1.305229;-1.305229;-1.066871;,
-1.533000;0.000000;-2.000000;,
-1.305229;-1.305229;-0.933129;,
-1.527681;0.000000;-0.250073;,
-1.080234;-1.080234;-0.250073;,
-1.845873;0.000000;-0.933129;,
-1.080234;-1.080234;0.250073;,
-1.784675;0.000000;0.932084;,
-1.261956;-1.261956;0.932084;,
-1.527681;0.000000;0.250073;,
-1.261956;-1.261956;1.067916;,
-1.533000;0.000000;2.000000;,
-1.083995;-1.083995;2.000000;,
-1.784675;0.000000;1.067916;,
-1.261956;1.261956;1.067916;,
-1.784675;0.000000;0.932084;,
-1.261956;1.261956;0.932084;,
-1.784675;0.000000;1.067916;,
0.000000;1.784675;1.067916;,
-1.261956;1.261956;0.932084;,
0.000000;1.784675;0.932084;,
-1.261956;1.261956;1.067916;,
1.261956;1.261956;1.067916;,
0.000000;1.784675;0.932084;,
1.261956;1.261956;0.932084;,
0.000000;1.784675;1.067916;,
1.784675;0.000000;1.067916;,
1.261956;1.261956;0.932084;,
1.784675;0.000000;0.932084;,
1.261956;1.261956;1.067916;,
1.261956;-1.261956;1.067916;,
1.784675;0.000000;0.932084;,
1.261956;-1.261956;0.932084;,
1.784675;0.000000;1.067916;,
0.000000;-1.784675;1.067916;,
1.261956;-1.261956;0.932084;,
0.000000;-1.784675;0.932084;,
1.261956;-1.261956;1.067916;,
-1.261956;-1.261956;1.067916;,
0.000000;-1.784675;0.932084;,
-1.261956;-1.261956;0.932084;,
0.000000;-1.784675;1.067916;,
-1.784675;0.000000;1.067916;,
-1.261956;-1.261956;0.932084;,
-1.784675;0.000000;0.932084;,
-1.261956;-1.261956;1.067916;,
-1.080234;1.080234;0.250073;,
-1.527681;0.000000;-0.250073;,
-1.080234;1.080234;-0.250073;,
-1.527681;0.000000;0.250073;,
0.000000;1.527681;0.250073;,
-1.080234;1.080234;-0.250073;,
0.000000;1.527681;-0.250073;,
-1.080234;1.080234;0.250073;,
1.080234;1.080234;0.250073;,
0.000000;1.527681;-0.250073;,
1.080234;1.080234;-0.250073;,
0.000000;1.527681;0.250073;,
1.527681;0.000000;0.250073;,
1.080234;1.080234;-0.250073;,
1.527681;0.000000;-0.250073;,
1.080234;1.080234;0.250073;,
1.080234;-1.080234;0.250073;,
1.527681;0.000000;-0.250073;,
1.080234;-1.080234;-0.250073;,
1.527681;0.000000;0.250073;,
0.000000;-1.527681;0.250073;,
1.080234;-1.080234;0.250073;,
0.000000;-1.527681;-0.250073;,
-1.080234;-1.080234;-0.250073;,
-1.527681;0.000000;0.250073;,
-1.080234;-1.080234;-0.250073;,
-1.527681;0.000000;-0.250073;,
-1.080234;-1.080234;0.250073;,
-1.305229;1.305229;-0.933129;,
-1.845873;0.000000;-1.066871;,
-1.305229;1.305229;-1.066871;,
-1.845873;0.000000;-0.933129;,
0.000000;1.845873;-0.933129;,
-1.305229;1.305229;-1.066871;,
0.000000;1.845873;-1.066871;,
-1.305229;1.305229;-0.933129;,
1.305229;1.305229;-0.933129;,
0.000000;1.845873;-1.066871;,
1.305229;1.305229;-1.066871;,
0.000000;1.845873;-0.933129;,
1.845873;0.000000;-0.933129;,
1.305229;1.305229;-1.066871;,
1.845873;0.000000;-1.066871;,
1.305229;1.305229;-0.933129;,
1.305229;-1.305229;-0.933129;,
1.845873;0.000000;-1.066871;,
1.305229;-1.305229;-1.066871;,
1.845873;0.000000;-0.933129;,
0.000000;-1.845873;-0.933129;,
1.305229;-1.305229;-1.066871;,
0.000000;-1.845873;-1.066871;,
1.305229;-1.305229;-0.933129;,
-1.305229;-1.305229;-0.933129;,
0.000000;-1.845873;-1.066871;,
-1.305229;-1.305229;-1.066871;,
0.000000;-1.845873;-0.933129;,
-1.845873;0.000000;-0.933129;,
-1.305229;-1.305229;-1.066871;,
-1.845873;0.000000;-1.066871;,
-1.305229;-1.305229;-0.933129;,
-1.316522;0.000000;1.848000;,
-0.930921;0.930921;1.848000;,
0.000000;0.000000;1.848000;,
0.000000;1.316522;1.848000;,
0.930921;0.930921;1.848000;,
1.316522;0.000000;1.848000;,
0.930921;-0.930921;1.848000;,
0.000000;-1.316522;1.848000;,
-0.930921;-0.930921;1.848000;,
-1.533000;0.000000;2.000000;,
-0.930921;0.930921;2.000000;,
-1.316522;0.000000;2.000000;,
-1.083995;1.083995;2.000000;,
0.000000;1.316522;2.000000;,
0.000000;1.533000;2.000000;,
0.930921;0.930921;2.000000;,
1.083995;1.083995;2.000000;,
1.316522;0.000000;2.000000;,
1.533000;0.000000;2.000000;,
0.930921;-0.930921;2.000000;,
1.083995;-1.083995;2.000000;,
0.000000;-1.316522;2.000000;,
0.000000;-1.533000;2.000000;,
-0.930921;-0.930921;2.000000;,
-1.083995;-1.083995;2.000000;,
-0.930921;0.930921;-1.848000;,
-1.316522;0.000000;-1.848000;,
0.000000;0.000000;-1.848000;,
0.000000;1.316522;-1.848000;,
0.930921;0.930921;-1.848000;,
1.316522;0.000000;-1.848000;,
0.930921;-0.930921;-1.848000;,
0.000000;-1.316522;-1.848000;,
-0.930921;-0.930921;-1.848000;,
-1.083995;1.083995;-2.000000;,
-1.316522;0.000000;-2.000000;,
-0.930921;0.930921;-2.000000;,
-1.533000;0.000000;-2.000000;,
-0.930921;-0.930921;-2.000000;,
-1.083995;-1.083995;-2.000000;,
0.000000;-1.316522;-2.000000;,
0.000000;-1.533000;-2.000000;,
0.930921;-0.930921;-2.000000;,
1.083995;-1.083995;-2.000000;,
1.316522;0.000000;-2.000000;,
1.533000;0.000000;-2.000000;,
0.930921;0.930921;-2.000000;,
1.083995;1.083995;-2.000000;,
0.000000;1.316522;-2.000000;,
0.000000;1.533000;-2.000000;,
-0.930921;0.930921;-2.000000;,
-1.316522;0.000000;-1.848000;,
-0.930921;0.930921;-1.848000;,
-1.316522;0.000000;-2.000000;,
-0.930921;-0.930921;-1.848000;,
-0.930921;-0.930921;-2.000000;,
-0.930921;-0.930921;-2.000000;,
0.000000;-1.316522;-1.848000;,
-0.930921;-0.930921;-1.848000;,
0.000000;-1.316522;-2.000000;,
0.000000;-1.316522;-2.000000;,
0.930921;-0.930921;-1.848000;,
0.000000;-1.316522;-1.848000;,
0.930921;-0.930921;-2.000000;,
0.930921;-0.930921;-2.000000;,
1.316522;0.000000;-1.848000;,
0.930921;-0.930921;-1.848000;,
1.316522;0.000000;-2.000000;,
1.316522;0.000000;-2.000000;,
0.930921;0.930921;-1.848000;,
1.316522;0.000000;-1.848000;,
0.930921;0.930921;-2.000000;,
0.930921;0.930921;-2.000000;,
0.000000;1.316522;-1.848000;,
0.930921;0.930921;-1.848000;,
0.000000;1.316522;-2.000000;,
0.000000;1.316522;-2.000000;,
-0.930921;0.930921;-1.848000;,
0.000000;1.316522;-1.848000;,
-0.930921;0.930921;-2.000000;,
-1.316522;0.000000;2.000000;,
-0.930921;0.930921;1.848000;,
-1.316522;0.000000;1.848000;,
-0.930921;0.930921;2.000000;,
-0.930921;0.930921;2.000000;,
0.000000;1.316522;1.848000;,
-0.930921;0.930921;1.848000;,
0.000000;1.316522;2.000000;,
0.000000;1.316522;2.000000;,
0.930921;0.930921;1.848000;,
0.000000;1.316522;1.848000;,
0.930921;0.930921;2.000000;,
0.930921;0.930921;2.000000;,
1.316522;0.000000;1.848000;,
0.930921;0.930921;1.848000;,
1.316522;0.000000;2.000000;,
1.316522;0.000000;2.000000;,
0.930921;-0.930921;1.848000;,
1.316522;0.000000;1.848000;,
0.930921;-0.930921;2.000000;,
0.930921;-0.930921;2.000000;,
0.000000;-1.316522;1.848000;,
0.930921;-0.930921;1.848000;,
0.000000;-1.316522;2.000000;,
0.000000;-1.316522;2.000000;,
-0.930921;-0.930921;1.848000;,
0.000000;-1.316522;1.848000;,
-0.930921;-0.930921;2.000000;,
-0.930921;-0.930921;2.000000;,
-1.316522;0.000000;1.848000;,
-0.930921;-0.930921;1.848000;,
-1.316522;0.000000;2.000000;;

 192;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;10,9,8;,
3;9,11,8;,
3;14,13,12;,
3;13,15,12;,
3;18,17,16;,
3;17,19,16;,
3;22,21,20;,
3;21,23,20;,
3;26,25,24;,
3;25,27,24;,
3;30,29,28;,
3;29,31,28;,
3;34,33,32;,
3;33,35,32;,
3;38,37,36;,
3;37,39,36;,
3;42,41,40;,
3;41,43,40;,
3;46,45,44;,
3;45,47,44;,
3;50,49,48;,
3;49,51,48;,
3;54,53,52;,
3;53,55,52;,
3;58,57,56;,
3;57,59,56;,
3;62,61,60;,
3;61,63,60;,
3;66,65,64;,
3;65,67,64;,
3;70,69,68;,
3;69,71,68;,
3;74,73,72;,
3;73,75,72;,
3;78,77,76;,
3;77,79,76;,
3;82,81,80;,
3;81,83,80;,
3;86,85,84;,
3;85,87,84;,
3;90,89,88;,
3;89,91,88;,
3;94,93,92;,
3;93,95,92;,
3;98,97,96;,
3;97,99,96;,
3;102,101,100;,
3;101,103,100;,
3;106,105,104;,
3;105,107,104;,
3;110,109,108;,
3;109,111,108;,
3;114,113,112;,
3;113,115,112;,
3;118,117,116;,
3;117,119,116;,
3;122,121,120;,
3;121,123,120;,
3;126,125,124;,
3;125,127,124;,
3;130,129,128;,
3;129,131,128;,
3;134,133,132;,
3;133,135,132;,
3;138,137,136;,
3;137,139,136;,
3;142,141,140;,
3;141,143,140;,
3;146,145,144;,
3;145,147,144;,
3;150,149,148;,
3;149,151,148;,
3;154,153,152;,
3;153,155,152;,
3;158,157,156;,
3;157,159,156;,
3;162,161,160;,
3;161,163,160;,
3;166,165,164;,
3;165,167,164;,
3;170,169,168;,
3;169,171,168;,
3;174,173,172;,
3;173,175,172;,
3;178,177,176;,
3;177,179,176;,
3;85,86,180;,
3;86,181,180;,
3;183,182,107;,
3;182,104,107;,
3;186,185,184;,
3;185,187,184;,
3;190,189,188;,
3;189,191,188;,
3;194,193,192;,
3;193,195,192;,
3;198,197,196;,
3;197,199,196;,
3;202,201,200;,
3;201,203,200;,
3;206,205,204;,
3;205,207,204;,
3;210,209,208;,
3;209,211,208;,
3;214,213,212;,
3;213,215,212;,
3;218,217,216;,
3;217,219,216;,
3;222,221,220;,
3;222,223,221;,
3;222,224,223;,
3;222,225,224;,
3;222,226,225;,
3;222,227,226;,
3;222,228,227;,
3;222,220,228;,
3;231,230,229;,
3;230,232,229;,
3;230,233,232;,
3;233,234,232;,
3;233,235,234;,
3;235,236,234;,
3;235,237,236;,
3;237,238,236;,
3;237,239,238;,
3;239,240,238;,
3;239,241,240;,
3;241,242,240;,
3;241,243,242;,
3;243,244,242;,
3;243,231,244;,
3;231,229,244;,
3;247,246,245;,
3;247,245,248;,
3;247,248,249;,
3;247,249,250;,
3;247,250,251;,
3;247,251,252;,
3;247,252,253;,
3;247,253,246;,
3;256,255,254;,
3;255,257,254;,
3;255,258,257;,
3;258,259,257;,
3;258,260,259;,
3;260,261,259;,
3;260,262,261;,
3;262,263,261;,
3;262,264,263;,
3;264,265,263;,
3;264,266,265;,
3;266,267,265;,
3;266,268,267;,
3;268,269,267;,
3;268,256,269;,
3;256,254,269;,
3;272,271,270;,
3;271,273,270;,
3;271,274,273;,
3;274,275,273;,
3;278,277,276;,
3;277,279,276;,
3;282,281,280;,
3;281,283,280;,
3;286,285,284;,
3;285,287,284;,
3;290,289,288;,
3;289,291,288;,
3;294,293,292;,
3;293,295,292;,
3;298,297,296;,
3;297,299,296;,
3;302,301,300;,
3;301,303,300;,
3;306,305,304;,
3;305,307,304;,
3;310,309,308;,
3;309,311,308;,
3;314,313,312;,
3;313,315,312;,
3;318,317,316;,
3;317,319,316;,
3;322,321,320;,
3;321,323,320;,
3;326,325,324;,
3;325,327,324;,
3;330,329,328;,
3;329,331,328;;
MeshMaterialList {
 1;
 192;
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
  0,
  0,
  0,
  0,
  0;;
Material {
 0.698039;0.698039;0.698039;1.000000;;
8.000000;
 0.752941;0.752941;0.752941;;
 0.059608;0.059608;0.059608;;
TextureFilename {
"bure2.bmp";
}
 }
}

 MeshNormals {
 332;
-0.882507;0.365547;-0.295899;,
-0.882507;0.365547;-0.295899;,
-0.882507;0.365547;-0.295900;,
-0.882508;0.365546;-0.295899;,
-0.848624;0.351512;0.395319;,
-0.848624;0.351512;0.395319;,
-0.848624;0.351511;0.395319;,
-0.848624;0.351512;0.395318;,
-0.872518;0.361408;-0.328780;,
-0.872518;0.361408;-0.328780;,
-0.872518;0.361409;-0.328780;,
-0.872518;0.361408;-0.328780;,
-0.896409;0.371304;0.242042;,
-0.896409;0.371304;0.242042;,
-0.896409;0.371304;0.242042;,
-0.896409;0.371304;0.242042;,
-0.365547;0.882507;-0.295899;,
-0.365547;0.882507;-0.295899;,
-0.365547;0.882507;-0.295899;,
-0.365546;0.882507;-0.295900;,
-0.351512;0.848624;0.395319;,
-0.351512;0.848624;0.395319;,
-0.351511;0.848624;0.395318;,
-0.351512;0.848624;0.395319;,
-0.361408;0.872518;-0.328780;,
-0.361408;0.872518;-0.328780;,
-0.361409;0.872518;-0.328780;,
-0.361408;0.872518;-0.328780;,
-0.371304;0.896409;0.242042;,
-0.371304;0.896409;0.242042;,
-0.371304;0.896409;0.242042;,
-0.371304;0.896409;0.242042;,
0.365547;0.882507;-0.295899;,
0.365547;0.882507;-0.295899;,
0.365547;0.882507;-0.295900;,
0.365546;0.882508;-0.295899;,
0.351512;0.848624;0.395319;,
0.351512;0.848624;0.395319;,
0.351511;0.848624;0.395319;,
0.351512;0.848624;0.395318;,
0.361408;0.872518;-0.328780;,
0.361408;0.872518;-0.328780;,
0.361409;0.872518;-0.328780;,
0.361408;0.872518;-0.328780;,
0.371304;0.896409;0.242042;,
0.371304;0.896409;0.242042;,
0.371304;0.896409;0.242042;,
0.371304;0.896409;0.242042;,
0.882507;0.365547;-0.295899;,
0.882507;0.365547;-0.295899;,
0.882507;0.365547;-0.295899;,
0.882507;0.365546;-0.295900;,
0.848624;0.351512;0.395319;,
0.848624;0.351512;0.395319;,
0.848624;0.351511;0.395318;,
0.848624;0.351512;0.395319;,
0.872518;0.361408;-0.328780;,
0.872518;0.361408;-0.328780;,
0.872518;0.361409;-0.328780;,
0.872518;0.361408;-0.328780;,
0.896409;0.371304;0.242042;,
0.896409;0.371304;0.242042;,
0.896409;0.371304;0.242042;,
0.896409;0.371304;0.242042;,
0.882507;-0.365547;-0.295899;,
0.882507;-0.365547;-0.295899;,
0.882507;-0.365547;-0.295900;,
0.882508;-0.365546;-0.295899;,
0.848624;-0.351512;0.395319;,
0.848624;-0.351512;0.395319;,
0.848624;-0.351511;0.395319;,
0.848624;-0.351512;0.395318;,
0.872518;-0.361408;-0.328780;,
0.872518;-0.361408;-0.328780;,
0.872518;-0.361409;-0.328780;,
0.872518;-0.361408;-0.328780;,
0.896409;-0.371304;0.242042;,
0.896409;-0.371304;0.242042;,
0.896409;-0.371304;0.242042;,
0.896409;-0.371304;0.242042;,
0.365547;-0.882507;-0.295899;,
0.365547;-0.882507;-0.295899;,
0.365547;-0.882507;-0.295899;,
0.365546;-0.882507;-0.295900;,
0.351512;-0.848624;0.395319;,
0.368636;-0.889967;0.268450;,
0.379220;-0.915519;0.134225;,
0.351512;-0.848624;0.395319;,
0.361408;-0.872518;-0.328780;,
0.361408;-0.872518;-0.328780;,
0.361409;-0.872518;-0.328780;,
0.361408;-0.872518;-0.328780;,
0.371304;-0.896409;0.242042;,
0.371304;-0.896409;0.242042;,
0.371304;-0.896409;0.242042;,
0.371304;-0.896409;0.242042;,
-0.365547;-0.882507;-0.295899;,
-0.365547;-0.882507;-0.295899;,
-0.365547;-0.882507;-0.295900;,
-0.365546;-0.882508;-0.295899;,
-0.351512;-0.848624;0.395319;,
-0.351512;-0.848624;0.395319;,
-0.351511;-0.848624;0.395319;,
-0.351512;-0.848624;0.395318;,
-0.373139;-0.900837;-0.221946;,
-0.361408;-0.872518;-0.328780;,
-0.361409;-0.872518;-0.328780;,
-0.380319;-0.918173;-0.110973;,
-0.371304;-0.896409;0.242042;,
-0.371304;-0.896409;0.242042;,
-0.371304;-0.896409;0.242042;,
-0.371304;-0.896409;0.242042;,
-0.882507;-0.365547;-0.295899;,
-0.882507;-0.365547;-0.295899;,
-0.882507;-0.365547;-0.295899;,
-0.882507;-0.365546;-0.295900;,
-0.848624;-0.351512;0.395319;,
-0.848624;-0.351512;0.395319;,
-0.848624;-0.351511;0.395318;,
-0.848624;-0.351512;0.395319;,
-0.872518;-0.361408;-0.328780;,
-0.872518;-0.361408;-0.328780;,
-0.872518;-0.361409;-0.328780;,
-0.872518;-0.361408;-0.328780;,
-0.896409;-0.371304;0.242042;,
-0.896409;-0.371304;0.242042;,
-0.896409;-0.371304;0.242042;,
-0.896409;-0.371304;0.242042;,
-0.923880;0.382683;0.000000;,
-0.923880;0.382683;0.000000;,
-0.923880;0.382683;0.000000;,
-0.923880;0.382683;0.000000;,
-0.382683;0.923880;0.000000;,
-0.382683;0.923880;0.000000;,
-0.382683;0.923880;0.000000;,
-0.382683;0.923880;0.000000;,
0.382683;0.923880;0.000000;,
0.382683;0.923880;0.000000;,
0.382683;0.923880;0.000000;,
0.382683;0.923880;0.000000;,
0.923880;0.382683;0.000000;,
0.923880;0.382683;0.000000;,
0.923880;0.382683;0.000000;,
0.923880;0.382683;0.000000;,
0.923880;-0.382683;0.000000;,
0.923880;-0.382683;0.000000;,
0.923880;-0.382683;0.000000;,
0.923880;-0.382683;0.000000;,
0.382683;-0.923880;0.000000;,
0.382683;-0.923880;0.000000;,
0.382683;-0.923880;0.000000;,
0.382683;-0.923880;0.000000;,
-0.382683;-0.923880;0.000000;,
-0.382683;-0.923880;0.000000;,
-0.382683;-0.923880;0.000000;,
-0.382683;-0.923880;0.000000;,
-0.923880;-0.382683;0.000000;,
-0.923880;-0.382683;0.000000;,
-0.923880;-0.382683;0.000000;,
-0.923880;-0.382683;0.000000;,
-0.923880;0.382683;0.000000;,
-0.923880;0.382683;0.000000;,
-0.923880;0.382683;0.000000;,
-0.923880;0.382683;0.000000;,
-0.382683;0.923880;0.000000;,
-0.382683;0.923880;0.000000;,
-0.382683;0.923880;0.000000;,
-0.382683;0.923880;0.000000;,
0.382683;0.923880;0.000000;,
0.382683;0.923880;0.000000;,
0.382683;0.923880;0.000000;,
0.382683;0.923880;0.000000;,
0.923880;0.382683;0.000000;,
0.923880;0.382683;0.000000;,
0.923880;0.382683;0.000000;,
0.923880;0.382683;0.000000;,
0.923880;-0.382683;0.000000;,
0.923880;-0.382683;0.000000;,
0.923880;-0.382683;0.000000;,
0.923880;-0.382683;0.000000;,
0.382683;-0.923880;0.000000;,
0.382683;-0.923880;0.000000;,
-0.382683;-0.923880;0.000000;,
-0.382683;-0.923880;0.000000;,
-0.923880;-0.382683;0.000000;,
-0.923880;-0.382683;0.000000;,
-0.923880;-0.382683;0.000000;,
-0.923880;-0.382683;0.000000;,
-0.923879;0.382684;0.000000;,
-0.923879;0.382684;0.000000;,
-0.923879;0.382684;0.000000;,
-0.923879;0.382684;0.000000;,
-0.382684;0.923879;0.000000;,
-0.382684;0.923879;0.000000;,
-0.382684;0.923879;0.000000;,
-0.382684;0.923879;0.000000;,
0.382684;0.923879;0.000000;,
0.382684;0.923879;0.000000;,
0.382684;0.923879;0.000000;,
0.382684;0.923879;0.000000;,
0.923879;0.382684;0.000000;,
0.923879;0.382684;0.000000;,
0.923879;0.382684;0.000000;,
0.923879;0.382684;0.000000;,
0.923879;-0.382684;0.000000;,
0.923879;-0.382684;0.000000;,
0.923879;-0.382684;0.000000;,
0.923879;-0.382684;0.000000;,
0.382684;-0.923879;0.000000;,
0.382684;-0.923879;0.000000;,
0.382684;-0.923879;0.000000;,
0.382684;-0.923879;0.000000;,
-0.382684;-0.923879;0.000000;,
-0.382684;-0.923879;0.000000;,
-0.382684;-0.923879;0.000000;,
-0.382684;-0.923879;0.000000;,
-0.923879;-0.382684;0.000000;,
-0.923879;-0.382684;0.000000;,
-0.923879;-0.382684;0.000000;,
-0.923879;-0.382684;0.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.923879;-0.382684;0.000000;,
0.990602;-0.136774;0.000000;,
0.923879;-0.382684;0.000000;,
0.990602;0.136774;0.000000;,
0.923879;0.382684;0.000000;,
0.923879;0.382684;0.000000;,
0.382684;0.923879;0.000000;,
0.382684;0.923879;0.000000;,
0.382684;0.923879;0.000000;,
0.382684;0.923879;0.000000;,
-0.382684;0.923879;0.000000;,
-0.382684;0.923879;0.000000;,
-0.382684;0.923879;0.000000;,
-0.382684;0.923879;0.000000;,
-0.923879;0.382684;0.000000;,
-0.923879;0.382684;0.000000;,
-0.923879;0.382684;0.000000;,
-0.923879;0.382684;0.000000;,
-0.923879;-0.382684;0.000000;,
-0.923879;-0.382684;0.000000;,
-0.923879;-0.382684;0.000000;,
-0.923879;-0.382684;0.000000;,
-0.382684;-0.923879;0.000000;,
-0.382684;-0.923879;0.000000;,
-0.382684;-0.923879;0.000000;,
-0.382684;-0.923879;0.000000;,
0.382684;-0.923879;0.000000;,
0.382684;-0.923879;0.000000;,
0.382684;-0.923879;0.000000;,
0.382684;-0.923879;0.000000;,
0.923879;-0.382684;0.000000;,
0.923879;-0.382684;0.000000;,
0.923879;-0.382684;0.000000;,
0.923879;-0.382684;0.000000;,
0.382684;-0.923879;0.000000;,
0.382684;-0.923879;0.000000;,
0.382684;-0.923879;0.000000;,
0.382684;-0.923879;0.000000;,
-0.382684;-0.923879;0.000000;,
-0.382684;-0.923879;0.000000;,
-0.382684;-0.923879;0.000000;,
-0.382684;-0.923879;0.000000;,
-0.923879;-0.382684;0.000000;,
-0.923879;-0.382684;0.000000;,
-0.923879;-0.382684;0.000000;,
-0.923879;-0.382684;0.000000;,
-0.923879;0.382684;0.000000;,
-0.923879;0.382684;0.000000;,
-0.923879;0.382684;0.000000;,
-0.923879;0.382684;0.000000;,
-0.382684;0.923879;0.000000;,
-0.382684;0.923879;0.000000;,
-0.382684;0.923879;0.000000;,
-0.382684;0.923879;0.000000;,
0.382684;0.923879;0.000000;,
0.382684;0.923879;0.000000;,
0.382684;0.923879;0.000000;,
0.382684;0.923879;0.000000;,
0.923879;0.382684;0.000000;,
0.923879;0.382684;0.000000;,
0.923879;0.382684;0.000000;,
0.923879;0.382684;0.000000;;

 192;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;10,9,8;,
3;9,11,8;,
3;14,13,12;,
3;13,15,12;,
3;18,17,16;,
3;17,19,16;,
3;22,21,20;,
3;21,23,20;,
3;26,25,24;,
3;25,27,24;,
3;30,29,28;,
3;29,31,28;,
3;34,33,32;,
3;33,35,32;,
3;38,37,36;,
3;37,39,36;,
3;42,41,40;,
3;41,43,40;,
3;46,45,44;,
3;45,47,44;,
3;50,49,48;,
3;49,51,48;,
3;54,53,52;,
3;53,55,52;,
3;58,57,56;,
3;57,59,56;,
3;62,61,60;,
3;61,63,60;,
3;66,65,64;,
3;65,67,64;,
3;70,69,68;,
3;69,71,68;,
3;74,73,72;,
3;73,75,72;,
3;78,77,76;,
3;77,79,76;,
3;82,81,80;,
3;81,83,80;,
3;86,85,84;,
3;85,87,84;,
3;90,89,88;,
3;89,91,88;,
3;94,93,92;,
3;93,95,92;,
3;98,97,96;,
3;97,99,96;,
3;102,101,100;,
3;101,103,100;,
3;106,105,104;,
3;105,107,104;,
3;110,109,108;,
3;109,111,108;,
3;114,113,112;,
3;113,115,112;,
3;118,117,116;,
3;117,119,116;,
3;122,121,120;,
3;121,123,120;,
3;126,125,124;,
3;125,127,124;,
3;130,129,128;,
3;129,131,128;,
3;134,133,132;,
3;133,135,132;,
3;138,137,136;,
3;137,139,136;,
3;142,141,140;,
3;141,143,140;,
3;146,145,144;,
3;145,147,144;,
3;150,149,148;,
3;149,151,148;,
3;154,153,152;,
3;153,155,152;,
3;158,157,156;,
3;157,159,156;,
3;162,161,160;,
3;161,163,160;,
3;166,165,164;,
3;165,167,164;,
3;170,169,168;,
3;169,171,168;,
3;174,173,172;,
3;173,175,172;,
3;178,177,176;,
3;177,179,176;,
3;85,86,180;,
3;86,181,180;,
3;183,182,107;,
3;182,104,107;,
3;186,185,184;,
3;185,187,184;,
3;190,189,188;,
3;189,191,188;,
3;194,193,192;,
3;193,195,192;,
3;198,197,196;,
3;197,199,196;,
3;202,201,200;,
3;201,203,200;,
3;206,205,204;,
3;205,207,204;,
3;210,209,208;,
3;209,211,208;,
3;214,213,212;,
3;213,215,212;,
3;218,217,216;,
3;217,219,216;,
3;222,221,220;,
3;222,223,221;,
3;222,224,223;,
3;222,225,224;,
3;222,226,225;,
3;222,227,226;,
3;222,228,227;,
3;222,220,228;,
3;231,230,229;,
3;230,232,229;,
3;230,233,232;,
3;233,234,232;,
3;233,235,234;,
3;235,236,234;,
3;235,237,236;,
3;237,238,236;,
3;237,239,238;,
3;239,240,238;,
3;239,241,240;,
3;241,242,240;,
3;241,243,242;,
3;243,244,242;,
3;243,231,244;,
3;231,229,244;,
3;247,246,245;,
3;247,245,248;,
3;247,248,249;,
3;247,249,250;,
3;247,250,251;,
3;247,251,252;,
3;247,252,253;,
3;247,253,246;,
3;256,255,254;,
3;255,257,254;,
3;255,258,257;,
3;258,259,257;,
3;258,260,259;,
3;260,261,259;,
3;260,262,261;,
3;262,263,261;,
3;262,264,263;,
3;264,265,263;,
3;264,266,265;,
3;266,267,265;,
3;266,268,267;,
3;268,269,267;,
3;268,256,269;,
3;256,254,269;,
3;272,271,270;,
3;271,273,270;,
3;271,274,273;,
3;274,275,273;,
3;278,277,276;,
3;277,279,276;,
3;282,281,280;,
3;281,283,280;,
3;286,285,284;,
3;285,287,284;,
3;290,289,288;,
3;289,291,288;,
3;294,293,292;,
3;293,295,292;,
3;298,297,296;,
3;297,299,296;,
3;302,301,300;,
3;301,303,300;,
3;306,305,304;,
3;305,307,304;,
3;310,309,308;,
3;309,311,308;,
3;314,313,312;,
3;313,315,312;,
3;318,317,316;,
3;317,319,316;,
3;322,321,320;,
3;321,323,320;,
3;326,325,324;,
3;325,327,324;,
3;330,329,328;,
3;329,331,328;;
 }
MeshTextureCoords {
 332;
0.050087;0.997424;,
0.347291;0.767831;,
0.015785;0.767831;,
0.311344;0.997424;,
0.016921;0.733910;,
0.310860;0.565847;,
0.055730;0.565847;,
0.348427;0.733910;,
0.055248;0.443156;,
0.350032;0.275349;,
0.017129;0.275349;,
0.310378;0.443156;,
0.017129;0.239717;,
0.320633;0.010381;,
0.046477;0.010381;,
0.350032;0.239717;,
0.051532;0.996594;,
0.348307;0.767001;,
0.016801;0.767001;,
0.312789;0.996594;,
0.018828;0.735108;,
0.311860;0.567044;,
0.056731;0.567044;,
0.350334;0.735108;,
0.055717;0.442142;,
0.350027;0.274336;,
0.017123;0.274336;,
0.310847;0.442142;,
0.017026;0.239901;,
0.319833;0.010565;,
0.045678;0.010565;,
0.349929;0.239901;,
0.051965;0.996594;,
0.348311;0.767001;,
0.016805;0.767001;,
0.313221;0.996594;,
0.015915;0.734094;,
0.310786;0.566031;,
0.055656;0.566031;,
0.347420;0.734094;,
0.056187;0.442972;,
0.350022;0.275165;,
0.017118;0.275165;,
0.311317;0.442972;,
0.017021;0.239717;,
0.320187;0.010381;,
0.046031;0.010381;,
0.349924;0.239717;,
0.051384;0.997791;,
0.347301;0.768198;,
0.015795;0.768198;,
0.312640;0.997791;,
0.016809;0.734461;,
0.310773;0.566398;,
0.055643;0.566398;,
0.348314;0.734461;,
0.057670;0.442972;,
0.351030;0.275599;,
0.018127;0.275165;,
0.312800;0.442972;,
0.016100;0.239717;,
0.320680;0.010381;,
0.046525;0.010381;,
0.349004;0.239717;,
0.051444;0.996594;,
0.348195;0.767001;,
0.016689;0.767001;,
0.312701;0.996594;,
0.016812;0.734094;,
0.311243;0.566031;,
0.056113;0.566031;,
0.348318;0.734094;,
0.057126;0.442326;,
0.350012;0.274519;,
0.017109;0.274519;,
0.312256;0.442326;,
0.017926;0.239901;,
0.320754;0.010565;,
0.046598;0.010565;,
0.350830;0.239901;,
0.051876;0.995580;,
0.348199;0.765987;,
0.016693;0.765987;,
0.313133;0.995580;,
0.015803;0.734278;,
0.310699;0.566214;,
0.055569;0.566214;,
0.347308;0.734278;,
0.057596;0.442142;,
0.350007;0.274769;,
0.017104;0.274335;,
0.312725;0.442142;,
0.015993;0.239717;,
0.320234;0.010381;,
0.046078;0.010381;,
0.348896;0.239717;,
0.050491;0.996581;,
0.346986;0.766988;,
0.015480;0.766988;,
0.311748;0.996581;,
0.017506;0.735095;,
0.310843;0.567032;,
0.055714;0.567032;,
0.349012;0.735095;,
0.056727;0.442959;,
0.350726;0.275153;,
0.017823;0.275153;,
0.311857;0.442959;,
0.016810;0.239705;,
0.320907;0.010369;,
0.046751;0.010369;,
0.349713;0.239705;,
0.051899;0.997595;,
0.347138;0.768002;,
0.015632;0.768002;,
0.313156;0.997595;,
0.015632;0.734425;,
0.310335;0.566362;,
0.055205;0.566362;,
0.347138;0.734425;,
0.055362;0.442959;,
0.350798;0.275153;,
0.017894;0.275153;,
0.310491;0.442959;,
0.017894;0.239705;,
0.320906;0.010369;,
0.046751;0.010369;,
0.350798;0.239705;,
0.349454;0.240159;,
0.016989;0.273322;,
0.349454;0.273580;,
0.016989;0.239901;,
0.350083;0.240326;,
0.016793;0.273138;,
0.350083;0.273313;,
0.016793;0.239717;,
0.349009;0.240731;,
0.016105;0.274152;,
0.349009;0.274152;,
0.016105;0.240731;,
0.350757;0.240518;,
0.015810;0.273505;,
0.350757;0.273939;,
0.015810;0.240085;,
0.349914;0.241098;,
0.017011;0.274519;,
0.349914;0.274519;,
0.017011;0.241098;,
0.349909;0.239901;,
0.017006;0.273322;,
0.349909;0.273322;,
0.017006;0.239901;,
0.350726;0.240718;,
0.017823;0.274139;,
0.350726;0.274139;,
0.017823;0.240718;,
0.350162;0.242600;,
0.018125;0.276021;,
0.350162;0.276021;,
0.018125;0.242600;,
0.310860;0.443802;,
0.055730;0.566861;,
0.310860;0.566861;,
0.055730;0.443802;,
0.311860;0.443156;,
0.056731;0.566214;,
0.311860;0.566214;,
0.056731;0.443156;,
0.310304;0.443986;,
0.055174;0.567044;,
0.310304;0.567044;,
0.055174;0.443986;,
0.310773;0.443986;,
0.055643;0.567044;,
0.310773;0.567044;,
0.055643;0.443986;,
0.310761;0.442788;,
0.055631;0.565847;,
0.310761;0.565847;,
0.055631;0.442788;,
0.310699;0.443156;,
0.055569;0.443156;,
0.056727;0.566018;,
0.311857;0.566018;,
0.311348;0.443303;,
0.056218;0.566362;,
0.311348;0.566362;,
0.056218;0.443303;,
0.347291;0.733910;,
0.015785;0.766817;,
0.347291;0.766817;,
0.015785;0.733910;,
0.348307;0.734924;,
0.016801;0.767831;,
0.348307;0.767831;,
0.016801;0.734924;,
0.348311;0.735108;,
0.016805;0.768015;,
0.348311;0.768015;,
0.016805;0.735108;,
0.347178;0.734094;,
0.015673;0.767001;,
0.347178;0.767001;,
0.015673;0.734094;,
0.348195;0.734278;,
0.016689;0.767185;,
0.348195;0.767185;,
0.016689;0.734278;,
0.348198;0.734278;,
0.016693;0.767185;,
0.348198;0.767185;,
0.016693;0.734278;,
0.347999;0.735095;,
0.016493;0.768002;,
0.347999;0.768002;,
0.016493;0.735095;,
0.348151;0.735095;,
0.016645;0.768002;,
0.348151;0.768002;,
0.016645;0.735095;,
0.400814;0.320974;,
0.478318;0.508086;,
0.665430;0.320974;,
0.665430;0.585590;,
0.852542;0.508086;,
0.930046;0.320974;,
0.852542;0.133863;,
0.665430;0.056359;,
0.478318;0.133863;,
0.357303;0.320974;,
0.478318;0.508086;,
0.400814;0.320974;,
0.447551;0.538853;,
0.665430;0.585590;,
0.665430;0.629102;,
0.852542;0.508086;,
0.883309;0.538853;,
0.930046;0.320974;,
0.973557;0.320974;,
0.852542;0.133863;,
0.883309;0.103096;,
0.665430;0.056359;,
0.665430;0.012847;,
0.478318;0.133863;,
0.447551;0.103096;,
0.479077;0.134622;,
0.401888;0.320975;,
0.665430;0.320975;,
0.665430;0.057432;,
0.851783;0.134622;,
0.928973;0.320975;,
0.851783;0.507327;,
0.665430;0.584517;,
0.479077;0.507327;,
0.448435;0.103979;,
0.401888;0.320975;,
0.479077;0.134622;,
0.358553;0.320975;,
0.479077;0.507327;,
0.448435;0.537970;,
0.665430;0.584517;,
0.665430;0.627852;,
0.851783;0.507327;,
0.882425;0.537970;,
0.928973;0.320975;,
0.972307;0.320975;,
0.851783;0.134622;,
0.882425;0.103979;,
0.665430;0.057432;,
0.665430;0.014097;,
0.990120;0.727697;,
0.369209;0.626462;,
0.990120;0.626462;,
0.369209;0.727697;,
0.990120;0.626462;,
0.990120;0.727697;,
0.370309;0.725653;,
0.990324;0.624418;,
0.370309;0.624418;,
0.990324;0.725653;,
0.369346;0.727697;,
0.989361;0.626462;,
0.369346;0.626462;,
0.989361;0.727697;,
0.371594;0.727697;,
0.992505;0.626462;,
0.371594;0.626462;,
0.992505;0.727697;,
0.989793;0.727697;,
0.368882;0.626462;,
0.989793;0.626462;,
0.368882;0.727697;,
0.989361;0.725653;,
0.369346;0.624418;,
0.989361;0.624418;,
0.369346;0.725653;,
0.990324;0.725653;,
0.370309;0.624418;,
0.990324;0.624418;,
0.370309;0.725653;,
0.364136;0.625169;,
0.995110;0.727295;,
0.364136;0.727295;,
0.995110;0.625169;,
0.377355;0.624866;,
0.993926;0.722075;,
0.377355;0.722075;,
0.993926;0.624866;,
0.365926;0.624866;,
0.974660;0.722075;,
0.365926;0.722075;,
0.974660;0.624866;,
0.389143;0.624866;,
0.997877;0.722075;,
0.389143;0.722075;,
0.997877;0.624866;,
0.374174;0.624866;,
0.982908;0.722075;,
0.374174;0.722075;,
0.982908;0.624866;,
0.371933;0.624866;,
0.980667;0.722075;,
0.371933;0.722075;,
0.980667;0.624866;,
0.374888;0.624866;,
0.983622;0.722075;,
0.374888;0.722075;,
0.983622;0.624866;,
0.372648;0.624866;,
0.981382;0.722075;,
0.372648;0.722075;,
0.981382;0.624866;;
}
}
 }