CXX := clang++

UI_DIR := ui
OUT_DIR := out
MOC_DIR := out/moc

SRCS := $(shell find . -iname '*.cpp' -not -path './out/*')
INCS := $(shell find . -iname '*.h' -o -iname '*.hpp' -not -path './out/*')
QT_INCS := $(shell find qt -iname '*.h' -not -path './out/*')

DEPS := $(addprefix $(OUT_DIR)/,$(sort $(patsubst %.cpp,def_%.d,$(notdir $(SRCS)))))

MOC_DEPS := $(addprefix $(MOC_DIR)/,$(sort $(patsubst %.h,moc_%.d,$(notdir $(QT_INCS)))))

OBJS := $(addprefix $(OUT_DIR)/,$(sort $(patsubst %.cpp,def_%.o,$(notdir $(SRCS)))))

MOC_OBJS := $(addprefix $(MOC_DIR)/,$(sort $(patsubst %.h,moc_%.o,$(notdir $(QT_INCS)))))

CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -Wno-unused-but-set-variable -Wfloat-equal $(addprefix -I,$(sort $(dir $(INCS)))) -I. $(shell pkgconf --cflags Qt6Widgets)
LDFLAGS := $(shell pkgconf --libs Qt6Widgets)

all : app.exe

app.exe : $(OBJS) $(MOC_OBJS)
	$(CXX) $^ $(LDFLAGS) -o ./app.exe

debug: CXXFLAGS += -g
debug: app.exe

$(MOC_DIR)/moc_%.o : $(OUT_DIR)/moc_%.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT_DIR)/def_%.o : $(filter %/$(patsubst def_%,%,$*).cpp,$(SRCS)) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -c $(filter %/$(patsubst def_%,%,$*).cpp,$(SRCS)) -o $@

$(MOC_DIR)/moc_%.d : $(MOC_DIR)/moc_%.cpp
	$(CXX) $(CXXFLAGS) -MM -MG -MF $@ -MT $(OUT_DIR)/def_$*.o $<

$(OUT_DIR)/def_%.d : $(filter %/$*.cpp,$(SRCS)) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -MM -MG -MF $@ -MT $(OUT_DIR)/def_$*.o $(filter %/$*.cpp,$(SRCS))

../../$(OUT_DIR)/ui_%.h : $(UI_DIR)/%.ui | $(OUT_DIR)
	/usr/lib/qt6/libexec/uic -o $(OUT_DIR)/$(notdir $@) $<

$(MOC_DIR)/moc_%.cpp : $(filter %/$*.h,$(QT_INCS)) | $(MOC_DIR)
	/usr/lib/qt6/libexec/moc -I. -o $@ $(filter %/$*.h,$(QT_INCS))

ifneq (clean, $(MAKECMDGOALS))
  include $(DEPS)
  include $(MOC_DEPS)
endif

$(OUT_DIR) : 
	mkdir -p $@

$(MOC_DIR) : 
	mkdir -p $@

clean :
	$(RM) -r $(OUT_DIR)/* ./*.exe

.PHONY : clean
.PRECIOUS : $(OUT_DIR)/moc_%.cpp
