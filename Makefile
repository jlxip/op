TARGET=op
GENERATED=y.tab.c lex.yy.c
SOURCES=$(GENERATED) $(wildcard *.cpp) $(wildcard interpreter/*.cpp)

all: $(TARGET)

$(TARGET): $(SOURCES)
	g++ $(SOURCES) -o $@

y.tab.c: op.y
	yacc $< -d -Wcounterexamples

lex.yy.c: op.l
	lex $<

.PHONY: clean
clean:
	rm -f $(TARGET) $(GENERATED) y.tab.h
