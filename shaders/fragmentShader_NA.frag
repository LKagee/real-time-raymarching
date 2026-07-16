#version 330 core
out vec4 FragColor;

#define T_MIN 0.0
#define T_MAX 10000.0

struct Sphere {
	vec3 pos;
	vec3 color;
	float radius;
};

float magnitude(vec3 u) {
	return sqrt(u.x*u.x + u.y*u.y + u.z*u.z);
}

float random_num(vec2 uv) {
	return fract(sin(dot(uv, vec2(12.9898, 48.2330)))*143758.5453123)+0.2;
}

vec3 adSphere(Sphere iSphere, vec3 D, vec3 O) {
	float t[2];
	vec3 new_D = O - iSphere.pos;
	float a = 1.0;
	float b = dot(2.0*D, new_D);
	float c = dot(new_D, new_D) - iSphere.radius * iSphere.radius;
	float determinate = b*b - 4.0*a*c;
	if(determinate < 0.0) {
		t[0] = -1.0;
		t[1] = -1.0;
	} else {
	t[0] = (-b - sqrt(determinate)) /2.0;
	t[1] = (-b + sqrt(determinate)) /2.0;
	}

	float closest_t = 10000.0;
	Sphere closest_sphere = Sphere(vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0), -1.0);
	if(t[0] < T_MAX && t[0] > T_MIN && t[0] < closest_t) {
		closest_t = t[0];
		closest_sphere = iSphere;
	}

	if(t[1] < T_MAX && t[1] > T_MIN && t[1] < closest_t) {
		closest_t = t[1];
		closest_sphere = iSphere;
	}

	if(closest_sphere.radius == -1.0) {
		return vec3(0.0, 0.0, 0.0);
	}
	return iSphere.color;

}


vec3 TraceRay(vec3 O, vec3 D) {
	return adSphere(Sphere(vec3(0.0, 0.0, 1.0), vec3(1.0, 0.0, 0.0), 1.0), D, O);
}

vec3 getSample(vec2 uv, vec3 O, float seed) {
	vec2 randVec = vec2(random_num(uv + vec2(seed, 0.0)) - 0.5, random_num(uv + vec2(0.0, seed) + vec2(0.32, 0.11)) - 0.5);
	randVec = randVec * (1.0/640.0);
	vec3 randSample = normalize(vec3(uv + randVec, 1.0));
	return TraceRay(O, randSample);
}

void main() {
	vec2 iResolution = vec2(640.0, 480.0);
	vec2 uv = (gl_FragCoord.xy - 0.5 * iResolution) / iResolution.y;
	vec3 camera = vec3(0.0, 0.0, -1.0);
	vec3 D = normalize(vec3(uv, 1.0));
	vec3 color = TraceRay(camera, D);
	FragColor = vec4(color, 1.0);
}
