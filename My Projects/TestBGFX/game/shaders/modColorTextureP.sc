$input v_color0, v_texcoord0
#include "common.sh"

SAMPLER2D(u_texColor, 0);

void main()
{
	gl_FragColor = texture2D(u_texColor, v_texcoord0.xy) * v_color0;
}