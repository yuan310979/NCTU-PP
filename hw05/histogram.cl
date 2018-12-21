__kernel void histogram(__global unsigned int *result, __constant unsigned int *img, __constant unsigned int *_size) {
    for(unsigned int i = 0; i < 768; i++)
        result[i] = 0;

	for (unsigned int i = 0; i < *_size; i += 3){
		unsigned int index = img[i];
		result[index]++;
	}

	result += 256;
	for (unsigned int i = 1; i < *_size; i += 3){
		unsigned int index = img[i];
		result[index]++;
	}

	result += 256;
	for (unsigned int i = 2; i < *_size; i += 3){
		unsigned int index = img[i];
		result[index]++;
	}
}
