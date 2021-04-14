attribute highp vec4 qt_Vertex;
attribute highp vec2 qt_MultiTexCoord0; //4 edi
uniform highp mat4 qt_ModelViewProjectionMatrix;
varying highp vec2 qt_TexCoord0; //4 edi

void main(void)
{
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    qt_TexCoord0 = qt_MultiTexCoord0;
}
