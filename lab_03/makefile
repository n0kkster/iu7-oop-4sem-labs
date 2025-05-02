CC := clang++

HEADERS_DIR := inc
SRC_DIR := src
UI_DIR := ui
OUT_DIR := out

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
INCS := $(wildcard $(HEADERS_DIR)/*.h)

DEPS := $(SRCS:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.d)
DEPS += $(INCS:$(HEADERS_DIR)/%.h=$(OUT_DIR)/moc_%.d)

OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)
OBJS += $(INCS:$(HEADERS_DIR)/%.h=$(OUT_DIR)/moc_%.o)

CFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -Wfloat-equal -I$(HEADERS_DIR) -I. $(shell pkgconf --cflags Qt6Widgets)
LFLAGS := $(shell pkgconf --libs Qt6Widgets)

all : app.exe

app.exe : $(OBJS)
	$(CC) $^ $(LFLAGS) -o ./app.exe


$(OUT_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.o : $(OUT_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.d : $(SRC_DIR)/%.cpp | $(OUT_DIR)
	$(CC) $(CFLAGS) -MM -MG -MF $@ -MT $(OUT_DIR)/$*.o $<

$(OUT_DIR)/%.d : $(OUT_DIR)/%.cpp
	$(CC) $(CFLAGS) -MM -MG -MF $@ -MT $(OUT_DIR)/$*.o $<

$(OUT_DIR)/ui_%.h : $(UI_DIR)/%.ui | $(OUT_DIR)
	/usr/lib/qt6/libexec/uic -o $@ $<

$(OUT_DIR)/moc_%.cpp : $(HEADERS_DIR)/%.h | $(OUT_DIR)
	/usr/lib/qt6/libexec/moc -I$(HEADERS_DIR) -I. -o $@ $<


ifneq (clean, $(MAKECMDGOALS))
  include $(DEPS)
endif

$(OUT_DIR) : 
	mkdir -p $@

clean :
	$(RM) $(OUT_DIR)/* ./*.exe

.PHONY : clean
.PRECIOUS : $(OUT_DIR)/moc_%.cpp
