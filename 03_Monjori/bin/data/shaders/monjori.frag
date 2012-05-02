#ifdef GL_ES
precision highp float;
#endif

//shader originally from : http://www.iquilezles.org/apps/shadertoy/

uniform vec2 resolution;
uniform float time;

uniform float time_factor ; 
uniform float e_factor ; 
uniform float f_factor ; 
uniform float i_factor ; 
uniform float d_factor ; 

uniform vec4 ambient_color ; 


void main(void)
{
    vec2 p = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
    
    float a = time*time_factor;
    float d,e,f,g=1.0/40.0,h,i,r,q;
    e = e_factor * (p.x*0.5+0.5);
    f = f_factor * (p.y*0.5+0.5);
    i = i_factor + sin(e*g+a/150.0)*20.0;
    d = d_factor + cos(f*g/2.0)*18.0+cos(e*g)*7.0;
    r=sqrt(pow(i-e,2.0)+pow(d-f,2.0));
    q=f/r;
    e=(r*cos(q))-a/2.0;f=(r*sin(q))-a/2.0;
    d=sin(e*g)*176.0+sin(e*g)*164.0+r;
    h=((f+d)+a/2.0)*g;
    i=cos(h+r*p.x/1.3)*(e+e+a)+cos(q*g*6.0)*(r+h/3.0);
    h=sin(f*g)*144.0-sin(e*g)*212.0*p.x;
    h=(h+(f-e)*q+sin(r-(a+h)/7.0)*10.0+i/4.0)*g;
    i+=cos(h*2.3*sin(a/350.0-q))*184.0*sin(q-(r*4.3+a/12.0)*g)+tan(r*g+h)*184.0*cos(r*g+h);
    

    i=mod(i/5.6,256.0)/64.0;
    
    //i=pow(i/5.6,2.0)/64.0;
   
    //    i=mod(i/5.6,2.0)/64.0;
   
     //   i=mod(i/5.6,128)/64.0;
        
    if(i<0.0) i+=4.0;
    if(i>=2.0) i=4.0-i;
    //d=r/350.0;
    d=r/350.0;
    d+=tan(sin(d*d*8.0)*0.52 ) * .75 ;
    f=(tan(a*g)+1.0)/2.0;
    vec4 color = vec4(vec3(f*i/1.6,i/2.0+d/13.0,i)*d*p.x+vec3(i/1.3+d/8.0,i/2.0+d/18.0,i)*d*(1.0-p.x),1.0) ;
    
    gl_FragColor = color + ambient_color ; 
}
