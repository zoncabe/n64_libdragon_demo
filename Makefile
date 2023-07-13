BUILD_DIR=build
include $(N64_INST)/include/n64.mk

src = gldemo.c sausage64.c

assets_ttf = $(wildcard assets/fonts/*.ttf)
assets_png = $(wildcard assets/textures/*.png)
assets_gltf = $(wildcard assets/models/*.gltf)

assets_conv = $(addprefix filesystem/,$(notdir $(assets_ttf:%.ttf=%.font64))) \
			  $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite)))\
              $(addprefix filesystem/,$(notdir $(assets_gltf:%.gltf=%.model64)))

MKSPRITE_FLAGS ?=

all: gldemo.z64

filesystem/%.font64: assets/fonts/%.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	@$(N64_MKFONT) $(MKFONT_FLAGS) -o filesystem "$<"

filesystem/%.sprite: assets/textures/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	@$(N64_MKSPRITE) -f RGBA16 --compress -o "$(dir $@)" "$<"

filesystem/%.model64: assets/models/%.gltf
	@mkdir -p $(dir $@)
	@echo "    [MODEL] $@"
	@$(N64_MKMODEL) -o "$(dir $@)" "$<"

filesystem/Pacifico.font64: MKFONT_FLAGS+=--size 18

$(BUILD_DIR)/gldemo.dfs: $(assets_conv)
$(BUILD_DIR)/gldemo.elf: $(src:%.c=$(BUILD_DIR)/%.o)

gldemo.z64: N64_ROM_TITLE="GL Demo"
gldemo.z64: $(BUILD_DIR)/gldemo.dfs

clean:
	rm -rf $(BUILD_DIR) filesystem/ gldemo.z64

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean
