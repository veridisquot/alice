#pragma once

#include "alice/core.h"

/* Forward decls */
typedef enum alice_TextureFlags alice_TextureFlags;
typedef struct alice_Texture alice_Texture;
typedef struct alice_Shader alice_Shader;
typedef struct alice_Material alice_Material;
typedef struct alice_Model alice_Model;

typedef enum alice_ResourceType {
	ALICE_RESOURCE_STRING,
	ALICE_RESOURCE_BINARY,
	ALICE_RESOURCE_TEXTURE,
	ALICE_RESOURCE_SHADER,
	ALICE_RESOURCE_ASSEMBLY,
	ALICE_RESOURCE_SCRIPT,
	ALICE_RESOURCE_MODEL,
	ALICE_RESOURCE_MATERIAL
} alice_ResourceType;

typedef struct alice_Resource {
	alice_ResourceType type;

	void* payload;
	u32 payload_size;

	i64 modtime;

	char* file_name;
	u32 file_name_length;
	u32 file_name_hash;
} alice_Resource;

ALICE_API void alice_init_resource_manager(const char* working_dir);
ALICE_API void alice_free_resource_manager();
ALICE_API void alice_init_default_resources();
ALICE_API void alice_free_resource(alice_Resource* resource);
ALICE_API void alice_free_resource_payload(alice_Resource* resource);
ALICE_API const char* alice_get_file_extension(const char* file_name);
ALICE_API const char* alice_get_file_name(const char* file_path);
ALICE_API alice_ResourceType alice_predict_resource_type(const char* file_extension);

ALICE_API const char* alice_get_texture_resource_filename(alice_Texture* texture);
ALICE_API const char* alice_get_shader_resource_filename(alice_Shader* shader);
ALICE_API const char* alice_get_material_resource_filename(alice_Material* material);
ALICE_API const char* alice_get_model_resource_filename(alice_Model* model);

ALICE_API void alice_get_working_dir(char* working_dir);

ALICE_API void alice_reload_changed_resources();

ALICE_API void alice_reload_resource(alice_Resource* resource);

ALICE_API alice_Resource* alice_load_binary(const char* path);
ALICE_API alice_Resource* alice_load_string(const char* path);
ALICE_API alice_Texture* alice_load_texture(const char* path, alice_TextureFlags flags);
ALICE_API alice_Shader* alice_load_shader(const char* path);
ALICE_API alice_Material* alice_load_material(const char* path);
ALICE_API alice_Model* alice_load_model(const char* path);

ALICE_API void alice_save_material(alice_Material* material, const char* path);

typedef void (*alice_ResourceIterateFunction)(const char* path, const char* extension,
	alice_ResourceType predicted_type, bool is_directory, void* ud);

ALICE_API void alice_iterate_resource_directory(const char* directory, alice_ResourceIterateFunction function, void* ud);
