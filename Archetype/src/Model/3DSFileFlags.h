#pragma once

#define MAIN_CHUNK 0x4d4d
	#define EDITOR_3D 0x3d3d

			#define MATERIAL_BLOCK 0xafff
				#define MATERIAL_NAME 0xa000
				#define AMBIENT_COLOR 0xa010
				#define DIFFUSE_COLOR 0xa020
				#define SPECULAR_COLOR 0xa030
				
					// Sub chunks for colours!
					#define RGB_COLOR 0x0011
					#define RGB_COLOR_LIN 0x0012

				#define SHININESS 0xa040
				#define SHINE_STRENGTH 0xa041
				#define TRANSPARENCY 0xa050
				#define TRANS_FALLOFF 0xa052
				#define REFLECTION_BLUR 0xa053
				#define SELF_ILLUMNATION 0xa084

					// Sub chunk for percentage
					#define PERCENTAGE 0x0030

				// Associated with the material type enum
				#define MATERIAL_TYPE 0xa100

				#define TEXTURE_MAP_1 0xa200
				#define TEXTURE_MAP_2 0xa33a
				#define OPACITY_MAP 0xa210
				#define BUMP_MAP 0xa230
				#define SPECULAR_MAP 0xa204
				#define REFLECTION_MAP 0xa220
					// Sub chunks for each map //
					#define MAPPING_FILENAME 0xa300
					#define MAPPING_PARAMETERS 0xa351

			#define OBJECT_BLOCK 0x4000
				#define TRIANGULAR_MESH 0x4100
				#define NAMED_OBJECT 0x4000
				#define VERTICES_LIST 0x4110
				#define FACES_DESCRIPTION 0x4120
					#define FACES_MATERIAL 0x4130
				#define MAPPING_COORDINATES_LIST 0x4140
					#define SMOOTHING_GROUP 0x4150
				#define TRANSLATION_MATRIX 0x4160