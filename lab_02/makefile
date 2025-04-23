CC := clang++

HEADERS_DIR := inc
SRC_DIR := src
UI_DIR := ui
OUT_DIR := out

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# INCS := $(find $(HEADERS_DIR) -iregex ".+\.h\(pp\)?")

DEPS := $(SRCS:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.d)

OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)

CFLAGS := -std=c++20 -O0 -Wall -Wextra -Wpedantic -Wfloat-equal -Wno-unknown-pragmas -Wno-pessimizing-move $(shell for f in inc/*; do echo -I $$f; done) 
LDFLAGS := -lm

all : app.exe

debug: CC = g++
debug: CFLAGS += -g
debug: app.exe 

app.exe : $(OBJS)
	$(CC) $^ $(LDFLAGS) -o ./app.exe

$(OUT_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.o : $(OUT_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.d : $(SRC_DIR)/%.cpp | $(OUT_DIR)
	$(CC) $(CFLAGS) -MM -MF $@ -MT $(OUT_DIR)/$*.o $<

$(OUT_DIR)/%.d : $(OUT_DIR)/%.cpp
	$(CC) $(CFLAGS) -MM -MF $@ -MT $(OUT_DIR)/$*.o $<

ifneq (clean, $(MAKECMDGOALS))
  include $(DEPS)
endif

$(OUT_DIR) : 
	mkdir -p $@

clean :
	$(RM) $(OUT_DIR)/* ./*.exe

.PHONY : clean