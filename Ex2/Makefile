# הגדרת המשתנה CXX שמציין את המהדר (קומפיילר) בו נשתמש, במקרה זה clang++
CXX = clang++
# הגדרת המשתנה CXXFLAGS שמציין את הדגלים שיש להעביר למהדר.
# -std=c++11 מגדיר שימוש בתקן C++11
# -Wall מגדיר הצגת כל ההתרעות (warnings)
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lm
TARGET = poisson
SRC = Poisson.cpp
LIB = libpoisson.so

# יצירת כלל ברירת מחדל שמקמפל את קובץ ההרצה TARGET
all: $(TARGET) $(LIB)

# כלל שמקמפל את קובץ ההרצה מ- SRC.
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# כלל ליצירת הספריה הדינמית
$(LIB): $(SRC)
	$(CXX) $(CXXFLAGS) -shared -o $(LIB) $(SRC) $(LDFLAGS)

# תוכנית המשתמשת בספריה ומחשבת התפלגות poisson עבור 5 ערכים
run: $(TARGET)
	./$(TARGET) 1 1
	./$(TARGET) 2 2
	./$(TARGET) 10 2
	./$(TARGET) 3 2
	./$(TARGET) 4 3

# Replace 3.5 and 2 with your desired lambda and k values
# כלל לניקוי קבצים שנוצרו (במקרה הזה קובץ ההרצה TARGET)
clean:
	rm -f $(TARGET) $(LIB)
