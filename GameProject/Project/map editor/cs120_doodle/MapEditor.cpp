
#include <Windows.h>
#include <doodle/doodle.hpp>
#include <fstream>
#include <WinUser.h>
using namespace doodle;

#include "std_lib_facilities.h"

struct Map
{
    int              width  = 0;
    int              height = 0;
    vector<unsigned> tiles{};
};

Map      map;
Map      map_prev;
unsigned NowColor = 0x000000FF;

 int widSize = 20;
 int heiSize = 20;
int           wid;
int           hei;
void          Save(Map& map);

void ColorChanger()
{
    unsigned short R;
    unsigned short G;
    unsigned short B;
    unsigned short A;
    ::SetWindowPos(GetConsoleWindow(), HWND_BOTTOM, 0, 0, 0, 0,
                   SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE);
    cout << "Input custom R in Hex: ";
    cin >> R;
    cout << "Input custom G in Hex: ";
    cin >> G;
    cout << "Input custom B in Hex: ";
    cin >> B;
    cout << "Input custom Alpha: ";
    cin >> A;
    NowColor = R << 24 | G << 16 | B << 8 | A;
    ::SetWindowPos(::FindWindow(NULL, ("doodle")), HWND_BOTTOM, 0, 0, 0, 0,
                   SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE);
}

void MarkLevel(int mouse_x, int mouse_y)
{
    const float tile_width   = static_cast<float>(Width) / static_cast<float>(map.width);
    const float tile_height  = static_cast<float>(Height) / static_cast<float>(map.height);
    const int   mouse_tile_x = static_cast<int>(static_cast<float>(mouse_x) / widSize);
    const int   mouse_tile_y = static_cast<int>(static_cast<float>(mouse_y) / heiSize);

    if (mouse_tile_x < 0 || mouse_tile_x >= map.width)
        return;
    if (mouse_tile_y < 0 || mouse_tile_y >= map.height)
        return;

    const int index  = map.width * mouse_tile_y + mouse_tile_x;
    map.tiles[index] = NowColor;
}

void DrawLevel(float tile_width, float tile_height) noexcept
{
    no_outline();
    for (int y = 0; y < map.height; y++)
    {
        for (int x = 0; x < map.width; x++)
        {
            const unsigned tile = map.tiles[map.width * y + x];
            set_fill_color(HexColor(tile));
            draw_rectangle(x * tile_width, y * tile_height, tile_width, tile_height);
        }
    }
}

void DrawCursor(const float tile_width, const float tile_height) noexcept
{
    const float mouse_x = tile_width * static_cast<int>(static_cast<float>(get_mouse_x()) / tile_width);
    const float mouse_y = tile_height * static_cast<int>(static_cast<float>(get_mouse_y()) / tile_height);
    set_fill_color(HexColor(NowColor));
    set_outline_color(255, 127);
    set_outline_width(3);
    draw_rectangle(mouse_x, mouse_y, tile_width, tile_height);
}


void on_key_released(KeyboardButtons button)
{
    switch (button)
    {
        case KeyboardButtons::C: ColorChanger(); break;
        case KeyboardButtons::S: Save(map); break;
        case KeyboardButtons::E: NowColor = 0; break;
        case KeyboardButtons::Z: map = map_prev; break;
        case KeyboardButtons::_1: NowColor = 0xFF0000FF; break;
        case KeyboardButtons::_2: NowColor = 0x00FF00FF; break;
        case KeyboardButtons::_3: NowColor = 0x0000FFFF; break;
        case KeyboardButtons::_4: NowColor = 0x000000FF; break;
        case KeyboardButtons::_5: NowColor = 0xFFFFFFFF; break;
        case KeyboardButtons::_6: NowColor = 0xFFFF00FF; break;
        case KeyboardButtons::_7: NowColor = 0xFF00FFFF; break;
        case KeyboardButtons::_8: NowColor = 0x00FFFFFF; break;
    }
}

void on_mouse_moved(int mouse_x, int mouse_y)
{
    if (!MouseIsPressed)
    {
        return;
    }
    else
    {
        MarkLevel(mouse_x, mouse_y);
    }
}

void on_mouse_pressed(MouseButtons) { 
	map_prev = map;
	MarkLevel(get_mouse_x(), get_mouse_y());
}

void Clear(Map& maaap)
{
    maaap.width  = wid;
    maaap.height = hei;
    maaap.tiles  = {};
    for (int i = 0; i < wid; i++)
    {
        for (int j = 0; j < hei; j++)
        {
            maaap.tiles.push_back(0);
        }
    }
}

ofstream& operator<<(ofstream& out, Map& maap)
{
    out << "width " << maap.width << endl << "height " << maap.height << endl;
    for (int y = 0; y < maap.height; y++)
    {
        for (int x = 0; x < maap.width; x++)
        {
            out << hex << maap.tiles[map.width * y + x] << ',';
        }
        out << '\n';
    }
    return out;
}

void Save(Map& map2)
{
    ::SetWindowPos(GetConsoleWindow(), HWND_BOTTOM, 0, 0, 0, 0,
                   SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE);
    string filename;
    cout << "I will save in this name: ";
    cin >> filename;
    ofstream output{filename + ".txt"};
    output.exceptions(output.exceptions() | ios_base::badbit);
    output << map2;
    cout << "Saved successfully!\n";
    close_window();
}

int HexDigitToDec(char hexDigit)
{
    char return_temp = 0;

	if ('a' <= hexDigit)
    {
        return_temp = (hexDigit - '7' - char(32));
	}
    else if ('A' <= hexDigit)
    {
        return_temp = (hexDigit - '7');
    }
    else if ('0' <= hexDigit)
    {
        return_temp = (hexDigit - '0');
    }

    return return_temp;
}

int ConvertHexToDec(string hexString)
{
    int result = 0;
    int len    = static_cast<int>(hexString.length()) - 1;
    while (len != -1)
    {
        result = HexDigitToDec(hexString[len]) * static_cast<int>(pow(16,len)) + result;
        len--;
    }
    return result;
}

istream& operator>>(istream& input, Map& maap)
{
    maap.tiles = {};
    string trash;
    char   get_char = '0';
    input >> trash >> maap.width >> trash >> maap.height;
    for (int y = 0; y < maap.height; y++)
    {
        for (int x = 0; x < maap.width; x++)
        {
            string value;
            while (1)
            {
                input >> get_char;
                if (get_char == ',')
                    break;
                value += get_char;
            }
            int result = ConvertHexToDec(value);
            maap.tiles.push_back(result);
        }
    }
    return input;
}

void Load(ifstream& fin)
{
    if (!fin)
    {
        error("Failed to read");
    }
    fin.exceptions(fin.exceptions() | ios_base::badbit);
    fin >> map;
}

int Minimum(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

int main(void)
try
{
    ::SetWindowPos(GetConsoleWindow(), HWND_BOTTOM, 0, 0, 0, 0,
                   SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE);
    cout << "e to edit the map\n";
    cout << "c to create new map: ";
    char select;
    cin >> select;
    if (select == 'e')
    {
        cout << "Drag the save file: ";
        string filePath;
        cin >> filePath;
        ifstream fin{filePath};
        Load(fin);
    }
    else if (select == 'c')
    {
        cout << "Give me the Width: ";
        cin >> wid;
        cout << "Give me the Height: ";
        cin >> hei;
        Clear(map);
    }


    create_window(map.width * widSize, map.height * heiSize);
    set_frame_of_reference(LeftHanded_OriginTopLeft);

    while (!is_window_closed())
    {
        update_window();
        clear_background(255);
        DrawLevel(static_cast<float>(widSize), static_cast<float>(heiSize));
        DrawCursor(static_cast<float>(widSize), static_cast<float>(heiSize));
    }
    return 0;
}
catch (exception& e)
{
    cerr << "Error: " << e.what() << "\n";
    keep_window_open();
    return -1;
}