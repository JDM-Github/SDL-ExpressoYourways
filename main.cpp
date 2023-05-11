/*
 * Simple Store for Data Structures and Algorithm
 * 
 * Who Code: John Dave C. Pega
 * WHo Made The Design: Baby Joy Maquilla
 * Others:
 *  Nica Jerusalem
 *  Kevin Carl Mico
 *  Carl James Macapanas
 *
 * 
 * NOTES: My OPINION (Wag basahin kung ayaw AHAHAHAH panget english)
 * The code i wrote here is not clean as you might think,
 * well it's because i made this code in only 1 day,
 * that's not good amount of time to spend on a project, but the reason i only have 1 or 2 days is
 * because the design got particularly late so i cannot start coding, since i don't know what i need
 * to make it look like. so yeahhhh, but overall im not complaining, others have life too
 * and im also pretty happy of the result i make anyway.
 * 
 * PS. all the components i used here is written by myself, if your wondering
 * But of course it wont be possible without SDL (Simple Direct Media)
 * this library has renderer and window creation, etc.
 * 
 * Anyways, Let's breakdown the code
 * 
 *  -> The Code OUTLINE
 * 
 *  Font I Used for this Project 
 *  -> BoldFont = I used this to Bold Text, highlighting TEXT
 *  -> SemiBoldFont = I used this as a normal font, i don't have time to find font for regular soooo
 * 
 *  Special Variables
 *  -> totalValueOfOrder = Used to get all the currentOrder totalValue and use it for many things, like evaluating the total and sub total
 *  -> currentCategory = Used to get what category im using, example category cuisine, includes: pizza, spaghetti, etc.
 *  -> currentUser = Used to get who currently is the user
 * 
 *  Special Struct
 *  -> Order = Order struct i used to make a structure for order, for easy use
 *  -> User = User is struct for user, this struct includes, all information on user
 * 
 *  Special Storage
 *  -> allCategories = This storage is "std::vector<std::string>" which means it is a collection of std::string
 *  -> allDishes = This storage is for all dishes, i used to know what is the category, std::map<std::string, std::vector<std::shared_ptr<Order>>>
 *  -> allUser = This storage is also a map, but the key is the username, and the value is the User struct
 * 
 *  Special Functions
 *  -> clearOrder = This is a function i used to clear the order and start to 0 the totalValue
 *  -> orderedOrder = This is a function for submitting the order,
 *         the order will check if it is possible to order and if it is, it will and order it and call cleanOrder
 *  -> addOrder = This is a function i used to add Order on my orderList
 *  -> removeOrder = This is a function i used to remove Order on my orderList (Pretty straight ain't it)
 *  -> and more (getTotalValue, checkIfAccountisAlreadyExist)
 * 
 *  BTW: Im using smart pointer, i don't want to waste my time and get a headache on creating this project by constantly checking
 *  if im freeing my allocated memory
 * 
 *  The syntax for smart pointer is
 *        std::unique_ptr : std::make_unique  -> used for non shareable heap memory, (faster)
 *        std::shared_ptr : std::make_shared  -> used for shareable heap memory (not the fast, but good enough)
 *        etc.
 * 
 */

#include "JDM/JDM.hpp"
#include <iomanip> // this is not included in my Library

// This is not mine, but it is just a handling json, it's for my needs
using json = nlohmann::json;

// Im using my OWN library so I know what to namespace and what not
using namespace JDM; // For my overall Library access
using namespace JDM::Comp; // For Components, JDM::Comp::Image, JDM::Comp::Text, etc

// Font i used (yeah only two)
std::string BoldFont = "Assets/ImageAsset/Store/Font/Genera-SemiBold.ttf";
std::string SemiBoldFont = "Assets/ImageAsset/Store/Font/SourceSansPro-SemiBold.ttf";


// Order Struct, pretty straight forward
// filePath: used to find the Image of this order, example hamburger.png, it will be use to JDM::Comp::Image
// nameOrder: used to get the name of the order and store it, so you know what your ordering is
// Price: yep, price

struct Order {
    std::string filePath = "";
    std::string nameOrder = "Food";
    float price = 0.f;

    Order(std::string file = "", std::string name = "Food", float p = 0.f, int q = 0)
        : filePath(file), nameOrder(name), price(p) {}
};

// User Struct, also pretty straightforward
// Name: for username or name for your account store
// Location: where you from, not really important because it's not really a store, just for aesthetic
// Budget: yep, budget, if your budget hits zero or your budget cannot buy anything, your account pretty much gone now
// Order History: used to get how much did you spend on your last order, i didn't make it complicated, just simple storage for float
// currentOrder: this store 

struct User {
    std::string name = "No Name";
    std::string location = "Unknown Location";
    float budget = 100.f;
    std::vector<float> orderHistory = {0, 0, 0, 0};
    std::vector<std::shared_ptr<Order>> currentOrder = {};
};

// All Special Variables
double totalValueOfOrder = 0;

// Special BOOLEAN, i use this, because my program cannot communicate through each other, because of heirarchy, and being local to each other
// using this global BOOLEAN variable, i can make them communicate, ( not the best way, but it works, soooo )

bool isInMenu = true; // used to make sure it is in menu
bool changed = false; // used to for trick (not very good too lazy to make it good)
bool updateHistory = false;
bool accessible = false; // used to make sure the JDM::Layout::BaseLayout is accessible
bool openSignIn = true; // used for trick on Sign in animation
bool updateDishes = false; // used to update dishes
std::string currentUser = "John";
std::string currentCategory = "Cuisine";

// All Special Storage
std::vector<std::string> allCategories = {"Cuisine", "Dessert", "FastFood"};
std::map<std::string, std::vector<std::shared_ptr<Order>>> allDishes;
std::map<std::string, User> allUser;

// Special Components, move to global for future use
std::shared_ptr<TextInput> searchBox = std::make_shared< TextInput>("", 240, 20, 570, 40);

// All Special Functions
void clearOrder() {
    allUser.at(currentUser).currentOrder.clear();
    totalValueOfOrder = 0;
}
bool orderedOrder() {
    if (allUser.at(currentUser).budget >= totalValueOfOrder && totalValueOfOrder > 0) {
        allUser.at(currentUser).orderHistory.push_back(totalValueOfOrder);
        allUser.at(currentUser).budget -= totalValueOfOrder;
        clearOrder();
        changed = true;
        return true;
    }
    return false;
}
void addOrder(std::shared_ptr<Order> order) {
    allUser.at(currentUser).currentOrder.push_back(order); changed = true;
    totalValueOfOrder += order->price;
}
void removeOrder(int index) {
    // I use algorithm library here
    totalValueOfOrder -= allUser.at(currentUser).currentOrder[(allUser.at(currentUser).currentOrder.size() - 1) - index]->price;
    allUser.at(currentUser).currentOrder.erase(std::find(
        allUser.at(currentUser).currentOrder.begin(),
        allUser.at(currentUser).currentOrder.end(),
        allUser.at(currentUser).currentOrder[(allUser.at(currentUser).currentOrder.size() - 1) - index]
    ));
    changed = true;
}
// Get the TOTAL value
void getTotalValue() { totalValueOfOrder = 0; for (const auto& ord: allUser.at(currentUser).currentOrder) totalValueOfOrder += ord->price; }

// Check if the account is already Exist, if it is return true
bool checkIfAccountisAlreadyExist(const std::string &user) { return allUser.count(user); }

// Load all the user that register in here from JSON
void loadJsonAllUser() {
    // Since i want to use json, but c++ have no support on json
    // I will use the code of the smart guy nlohmann for this JSON library
    std::ifstream inputFile("Json/allUser.json");
    json jsonData;
    inputFile >> jsonData;

    // Fill the User with Json value
    for (const auto& [username, userData] : jsonData.items()) {
        User user;
        user.name = userData.value("name", "No Name");
        user.location = userData.value("location", "Unknown Location");
        user.budget = userData.value("budget", 100.f);
        const auto& orderHistoryData = userData["orderHistory"];
        if (orderHistoryData.is_array()) { user.orderHistory = orderHistoryData.get<std::vector<float>>(); }
        allUser[username] = user;
    }
    currentUser = allUser.begin()->first;

    // Since where here anyway, I will also fill the all dishes that depends on JSON
    // Using that, i can just edit the json and the code will change even without compiling it again and again
    std::ifstream inputFileDish("Json/allDishes.json");
    json jsonDataDishes;
    inputFileDish >> jsonDataDishes;

    for (auto it = jsonDataDishes.begin(); it != jsonDataDishes.end(); ++it) {

        // Get the key and the value of the JSON
        const std::string &category = it.key();
        const json& dishes = it.value();

        for (auto dishIt = dishes.begin(); dishIt != dishes.end(); ++dishIt) {

            // Loop through all value of Main Key and also get the key and value of that
            const std::string &dishName = dishIt.key();
            const json& dishData = dishIt.value();
            std::string filePath = dishData["filePath"];
            float price = dishData["value"];
            allDishes[category].push_back(std::make_shared<Order>(filePath, dishName, price));
        }
    }
    currentCategory = allDishes.begin()->first;
}

// Save all the user that register in here in JSON
void saveJsonAllUser() {
    json jsonData;

    for (const auto& entry : allUser) {
        const std::string& key = entry.first;
        const User& user = entry.second;

        jsonData[key]["name"] = user.name;
        jsonData[key]["budget"] = user.budget;
        jsonData[key]["location"] = user.location;

        for (const auto& order : user.orderHistory)
            jsonData[key]["orderHistory"].push_back(order);
    }

    // Save the Json data to a file
    std::ofstream outputFile("Json/allUser.json");
    if (outputFile.is_open()) {
        outputFile << jsonData.dump(4);
        outputFile.close();
    }
}
/*
 * i will not going to explain the class I made, or functionality it has, because
 * it is mainly created using my Library JDM
*/

/////////////////////////////////////////////////////////
//
// -> NOTIFICATION CLASS
// -> Just a class for handling notification, it has open and show
//
/////////////////////////////////////////////////////////

class Notification : public Layout::BaseLayout {
public:
    std::shared_ptr<Image> iconNotif = std::make_shared<Image>(
        "Assets/ImageAsset/Store/Icon/notificon.png", 20, 630, 30, 30, ColorRGBA{255, 255, 255, 0});
    std::shared_ptr<Image> backGround = std::make_shared<Image>(
        DefaultImage, 10, 580, 300, 100, ColorRGBA{0x3f, 0x3f, 0x3f, 0}, 30);
    std::shared_ptr<Text> mess = std::make_shared<Text>(
        "Notification", 70, 620, 300, 60, ColorRGBA{0xff, 0xff, 0xff, 0}, 10, JDM::Font::LEFT);
    std::shared_ptr<Text> expresso = std::make_shared<Text>(
        "Expresso Yourway", 20, 580, 300, 40, ColorRGBA{0xff, 0xff, 0xff, 0}, 8);

    Notification() {
        mess->setFontRegular(BoldFont);
        expresso->setFontRegular(SemiBoldFont);
        this->addComponents(backGround);
        this->addComponents(iconNotif);
        this->addComponents(expresso);
        this->addComponents(mess);
    }
    void show(const std::string &message) {
        mess->setText(message);
        mess->setAForeGround(255);
        expresso->setAForeGround(255);
        iconNotif->setAImage(255);
        backGround->setAImage(255);
        this->close();
    }
    void close() {
        JDM::Window::addStartAnimation(std::make_shared<JDM::Animation<uint8_t>>(iconNotif->getPointerAImage(), 1, 2, true));
        JDM::Window::addStartAnimation(std::make_shared<JDM::Animation<uint8_t>>(backGround->getPointerAImage(), 1, 2, true));
        JDM::Window::addStartAnimation(std::make_shared<JDM::Animation<uint8_t>>(mess->getPointerAForeGround(), 1, 2, true));
        JDM::Window::addStartAnimation(std::make_shared<JDM::Animation<uint8_t>>(expresso->getPointerAForeGround(), 1, 2, true));
    }
};
std::shared_ptr<Notification> notif;

/////////////////////////////////////////////////////////
//
// -> CATEGORIES CLASS
// -> Just a class for handling Categories
//
/////////////////////////////////////////////////////////

class Categories : public Layout::BaseLayout {
public:
    // Class inside class
    class Category : public Canvas::Circle {
    public:
        std::string filePath;
        std::shared_ptr<Image> image;
        Category(const std::string& path, double x) :
            filePath(path), Canvas::Circle(x, 150, 75, 75, JDM::getColorFromHexA("6d6d6dff")) {
            image = std::make_shared<Image>("Assets/ImageAsset/Store/" + filePath + "/1.png", x+12.5, 150+12.5, 50, 50);

            this->setmouseDownFunction([&](SDL_MouseButtonEvent &mouse) {
                currentCategory = filePath;
                updateDishes = true;
            });
        }
        const void update() { 
            if (filePath != currentCategory) {
                image->setAImage(100);
                this->setAImage(100);
            } else {
                image->setAImage(255);
                this->setAImage(255);
            }
            Canvas::Circle::update(); image->update();
        }
        const void renderComp() { Canvas::Circle::renderComp(); image->renderComp(); }
    };
    Text categorytext = Text(std::to_string(allCategories.size()) + "+ New Categories added this week", 250, 120, 300, 20, JDM::getColorFromHexA("dfdfdfaa"));
    std::shared_ptr<Text> categoriesText = std::make_shared<Text>("Categories", 250, 100, 300, 30);

    Categories() {
        categoriesText->setFontSize(10);
        categoriesText->setHalign(JDM::Font::LEFT);
        categoriesText->setFontRegular(BoldFont);

        categorytext.setFontSize(8);
        categorytext.setHalign(JDM::Font::LEFT);
        categorytext.setFontRegular(SemiBoldFont);
        this->addComponents(categoriesText);

        int number = 0;
        for (auto &cat : allCategories) {
            this->addComponents(std::make_shared<Category>(cat, 250 + (75*number) + (10*number++))); }
    }

    const void update() { Layout::BaseLayout::update(); categorytext.update(); }
    const void renderComp() { Layout::BaseLayout::renderComp(); categorytext.renderComp(); }
};

/////////////////////////////////////////////////////////
//
// -> DISHES CLASS
// -> Just a class for handling Dishes
//
/////////////////////////////////////////////////////////

class Dishes : public Layout::BaseLayout {
public:
    class Dish : public Button {
    public:
        std::string filePath;
        std::shared_ptr<Image> image;
        std::shared_ptr<Order> myOrder;

        Text text = Text("Starting From", 0, 0, 0, 0, JDM::getColorFromHexA("dcdcdcff"));
        Text priceText = Text();
        float price;

        Dish(const std::shared_ptr<Order> &order, double x, double y) : 
            price(order->price), filePath(order->filePath), Button(order->nameOrder, RoundedImage, x, y, 125, 125,
            JDM::getColorFromHexA("ffffffff"), JDM::getColorFromHexA("323232ff"),
            JDM::getColorFromHexA("2d2d2dff")) {

            myOrder = std::make_shared<Order>(
                "Assets/ImageAsset/Store/" + currentCategory + "/" + order->filePath,
                order->nameOrder, order->price);

            text.setSize({125, 30});
            text.setPos({x, y + (125/2.f) + 5});
            text.setFontRegular(SemiBoldFont);
            text.setFontSize(6);
            
            priceText.setSize({125, 30});
            priceText.setPos({x, y + (125/2.f) + 5+20});
            priceText.setFontRegular(SemiBoldFont);
            priceText.setFontSize(8);

            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << price;
            priceText.setText("$ " + ss.str());

            this->setFontSize(10);
            this->setFontRegular(BoldFont);
            image = std::make_shared<Image>(myOrder->filePath, x+22.5, y - 40, 80, 80);
            this->setmouseDownFunction([&](SDL_MouseButtonEvent &mouse) { if (isInMenu) addOrder(myOrder); });
        }
        
        const void update() {
            Button::update(); image->update();
            text.update(); priceText.update();
        }
        const void renderComp() {
            Button::renderComp(); image->renderComp();
            text.renderComp(); priceText.renderComp();
        }
    };
    Text dishtext = Text(std::to_string(allDishes.at(currentCategory).size()) + "+ dishes are avaible in this week", 250, 270, 300, 20, JDM::getColorFromHexA("dfdfdfaa"));

    std::shared_ptr<Layout::BaseLayout> allDish = std::make_shared<Layout::BaseLayout>();
    std::shared_ptr<Text> dishText = std::make_shared<Text>("Popular Dishes", 250, 250, 300, 30);

    Dishes() {
        dishText->setFontSize(10);
        dishText->setHalign(JDM::Font::LEFT);
        dishText->setFontRegular(BoldFont);

        dishtext.setFontSize(8);
        dishtext.setHalign(JDM::Font::LEFT);
        dishtext.setFontRegular(SemiBoldFont);
        this->addComponents(dishText);
        this->addComponents(allDish);

        addAllTheDishComponents();
    }
    const void addAllTheDishComponents() {
        allDish->childrens.clear();
        int number = 0;
        for (const auto &dish : allDishes.at(currentCategory)) {
            if (searchBox->getText().empty() || dish->nameOrder.find(searchBox->getText()) != std::string::npos) {
                int x = number % 4;
                int y = number / 4;
                allDish->addComponents(std::make_shared<Dish>(dish, 250 + (125*x) + (10*x), 350 + (125*y) + (50*y)));
                number++;
            }
            
        }
    }
    const void update() {
        if (updateDishes) {
            addAllTheDishComponents();
            updateDishes = false;
        }
        Layout::BaseLayout::update(); dishtext.update();
    }
    const void renderComp() { Layout::BaseLayout::renderComp(); dishtext.renderComp(); }
};

/////////////////////////////////////////////////////////
//
// -> DASHBOARD CLASS
// -> Just a class for Dashboard, the one on the LEFT
//
/////////////////////////////////////////////////////////

class DashBoard : public Layout::BaseLayout {
public:
    class Navigation : public Layout::BaseLayout {
    public:
        std::shared_ptr<Image> icon = std::make_shared<Image>(RoundedImage,  20, 197.5, 30, 30);
        std::shared_ptr<Text> text = std::make_shared<Text>("", 100, 210, 100, 30);
        Navigation(const std::string &iconPath, const std::string t, int number, ColorRGBA color = {180, 180, 180, 255}) {

            // HARD CODEEEE BABYY

            icon->setSource(iconPath);
            icon->setY(210 + (62.5 * number) + (30 * number));
            icon->setColor(color);
            text->setText(t);
            text->setFontSize(10);
            text->setFontRegular(BoldFont);
            text->setHalign(JDM::Font::LEFT);
            text->setForeGroundColor(color);
            text->setY(210 + (62.5 * number) + (30 * number));
            this->addComponents(icon);
            this->addComponents(text);
        }
    };

    std::shared_ptr<Canvas::Rectangle> rectDash = std::make_shared<Canvas::Rectangle>( 0, 0, 200, 700, JDM::getColorFromHexA("3d3d3dff"));
    std::shared_ptr<Image> iconHolder = std::make_shared<Image>(DefaultImage, -25, 125, 100, 500, JDM::getColorFromHexA("6d6d6dff"));
    std::shared_ptr<Image> icon = std::make_shared<Image>("Assets/ImageAsset/Store/Icon/icon.png", 50, 20, 100, 100);
    std::shared_ptr<Navigation> menu = std::make_shared<Navigation>("Assets/ImageAsset/Store/Icon/menuicon.png", "Menu", 0, JDM::getColorFromHexA("ffffffff"));
    std::shared_ptr<Navigation> user = std::make_shared<Navigation>("Assets/ImageAsset/Store/Icon/accounticon.png", "Account", 1);
    std::shared_ptr<Navigation> order = std::make_shared<Navigation>("Assets/ImageAsset/Store/Icon/order.png", "Orders", 2);
    std::shared_ptr<Navigation> logout = std::make_shared<Navigation>("Assets/ImageAsset/Store/Icon/logout.png", "Logout", 3);

    class History : public Label {
    public:
        bool hasOrder = false; int number = 0; float oldValue = 0;
        Text text = Text("", 290, 0, 470, 40, JDM::getColorFromHexA("dfdfdfff"), 8, JDM::Font::RIGHT);
        History(float total, int number1) : number(number1), Label( "Completed", DefaultImage, 290, 390+700 + (50*(number1+1)), 100, 40,
                {0xff, 0xff, 0xff, 0xff}, {0x2b, 0x87, 0x2f, 0xff}, 20, 8) {
            text.setY(this->getY());
            this->setFontRegular(SemiBoldFont);
            text.setFontRegular(SemiBoldFont);
        }
        const void update() {

            // UPDATE USER HISTORY (STOP.)
            if (((allUser.at(currentUser).orderHistory.size() - 1) - number) >= 0) {
            if (updateHistory) {
                text.setText("");
                hasOrder = false;
                oldValue = 0;
            }
            if (oldValue != allUser.at(currentUser).orderHistory[(allUser.at(currentUser).orderHistory.size() - 1) - number] &&
            allUser.at(currentUser).orderHistory[(allUser.at(currentUser).orderHistory.size() - 1) - number] > 0) {
                hasOrder = true;
                std::stringstream ss;
                ss << "$ " << std::fixed << std::setprecision(2) <<
                    allUser.at(currentUser).orderHistory[(allUser.at(currentUser).orderHistory.size() - 1) - number];
                text.setText(ss.str());
                oldValue = allUser.at(currentUser).orderHistory[(allUser.at(currentUser).orderHistory.size() - 1) - number];
            }} else { hasOrder = false; }
            Label::update(); text.setY(this->getY()); text.update();
        }
        const void renderComp() {
            SDL_SetRenderDrawColor(JDM::renderer, 0x6d, 0x6d, 0x6d, 255);
            SDL_RenderDrawLineF(JDM::renderer, 290, this->getY(), 290 + 470, this->getY());
            if (hasOrder) Label::renderComp(); text.renderComp();
            SDL_SetRenderDrawColor(JDM::renderer, 0x6d, 0x6d, 0x6d, 255);
            SDL_RenderDrawLineF(JDM::renderer, 290, this->getY()+40, 290 + 470, this->getY()+40);
        }
    };

    /////////////////////////////////////////////////////////
    //
    // -> ACCOUNT UI CLASS
    // -> This class is inside of Dashboard, because, well i don't have access on it, if it is outside, Dashboard class
    //
    /////////////////////////////////////////////////////////

    class AccountUI : public Layout::BaseLayout {
    public:
        bool opened = false;
        std::shared_ptr<Image> userProfile = std::make_shared<Image>( "Assets/ImageAsset/Store/Icon/accounticon.png", 270, 110+700, 200, 200);
        std::shared_ptr<Image> backGround = std::make_shared<Image>( DefaultImage, 240, 80+700, 570, 680, JDM::getColorFromHexA("3d3d3dff"));
        std::shared_ptr<Text> name = std::make_shared<Text>( "", 490, 150+700, 220, 50, JDM::getColorFromHexA("ffffffff"), 14, JDM::Font::LEFT);
        std::shared_ptr<Canvas::Line> lineName = std::make_shared<Canvas::Line>( 490, 190+700, 220, 190+700, JDM::getColorFromHexA("6d6d6dff"));
        std::shared_ptr<Text> location = std::make_shared<Text>( "", 490, 230+700, 220, 30, JDM::getColorFromHexA("dfdfdfff"), 10, JDM::Font::LEFT);
        std::shared_ptr<Text> budget = std::make_shared<Text>( "$ ", 490, 270+700, 220, 30, JDM::getColorFromHexA("dfdfdfff"), 10, JDM::Font::LEFT);
        std::shared_ptr<Text> orderHistory = std::make_shared<Text>( "Order History", 270, 340+700, 220, 30, JDM::getColorFromHexA("ffffffff"), 14, JDM::Font::LEFT);
        std::shared_ptr<Image> format = std::make_shared<Image>( DefaultImage, 270, 380+700, 510, 50, JDM::getColorFromHexA("2f2f2fff"));
        std::shared_ptr<Text> status = std::make_shared<Text>( "Status", 290, 380+700, 470, 50, JDM::getColorFromHexA("dfdfdfff"), 10, JDM::Font::LEFT);
        std::shared_ptr<Text> amount = std::make_shared<Text>( "Amount", 290, 380+700, 470, 50, JDM::getColorFromHexA("dfdfdfff"), 10, JDM::Font::RIGHT);

        std::vector<std::shared_ptr<History>> allHistory = {
            std::make_shared<History>(0, 0),
            std::make_shared<History>(0, 1),
            std::make_shared<History>(0, 2),
            std::make_shared<History>(0, 3),
        };

        AccountUI() {
            name->setFontRegular(BoldFont);
            orderHistory->setFontRegular(BoldFont);
            location->setFontRegular(SemiBoldFont);
            budget->setFontRegular(SemiBoldFont);
            format->setArc(30);

            backGround->setArcTL(30);
            backGround->setArcTR(30);
            userProfile->setArc(30);
            this->addComponents(backGround);
            this->addComponents(userProfile);
            this->addComponents(name);
            this->addComponents(lineName);

            this->addComponents(location);
            this->addComponents(budget);
            this->addComponents(orderHistory);
            this->addComponents(format);
            this->addComponents(status);
            this->addComponents(amount);
            for (const auto &his: allHistory) { this->addComponents(his); }
        }
        void open() {
            if (opened) return;

            opened = true;
            name->setText(allUser.at(currentUser).name);
            std::stringstream ss;
            ss << "$ " << std::fixed << std::setprecision(2) << allUser.at(currentUser).budget;
            budget->setText(ss.str());
            location->setText(allUser.at(currentUser).location);
            this->moveAllYSmooth(-700, 0.2);
        }
        void close() { if (opened) this->moveAllYSmooth(700, 0.2); opened = false; }
        const void update() {
            Layout::BaseLayout::update();
            lineName->setPos({490, name->getY() + 50});
            lineName->setSize({490 + 220, name->getY() + 50});
            updateHistory = false;
        }
    };
    std::shared_ptr<AccountUI> accountUI = std::make_shared<AccountUI>();
    DashBoard() {
        iconHolder->setArcTR(90);
        iconHolder->setArcBR(90);
        rectDash->setGradient(VERTICAL);
        rectDash->setGradiendColor(JDM::getColorFromHexA("3d3d3dff"), JDM::getColorFromHexA("1d1d1dff"));
        this->addComponents(rectDash);
        this->addComponents(icon);
        this->addComponents(iconHolder);

        this->addComponents(menu);
        this->addComponents(user);
        this->addComponents(order);
        this->addComponents(logout);
        this->addComponents(accountUI);

        // TOO LAZY TO FIX THIS, THIS IS GOOD ENOUGH, ATLEAST IT WORKS
        menu->icon->setmouseDownFunction([&](SDL_MouseButtonEvent &mouse) {
            menu->icon->setColor({255, 255, 255, 255});
            menu->text->setForeGroundColor({255, 255, 255, 255});
            user->icon->setColor({180, 180, 180, 255});
            user->text->setForeGroundColor({180, 180, 180, 255});
            order->icon->setColor({180, 180, 180, 255});
            order->text->setForeGroundColor({180, 180, 180, 255});
            logout->icon->setColor({180, 180, 180, 255});
            logout->text->setForeGroundColor({180, 180, 180, 255});
            isInMenu = true;
            accountUI->close();
        });
        user->icon->setmouseDownFunction([&](SDL_MouseButtonEvent &mouse) {
            user->icon->setColor({255, 255, 255, 255});
            user->text->setForeGroundColor({255, 255, 255, 255});
            menu->icon->setColor({180, 180, 180, 255});
            menu->text->setForeGroundColor({180, 180, 180, 255});
            order->icon->setColor({180, 180, 180, 255});
            order->text->setForeGroundColor({180, 180, 180, 255});
            logout->icon->setColor({180, 180, 180, 255});
            logout->text->setForeGroundColor({180, 180, 180, 255});
            isInMenu = false;
            accountUI->open();
        });
        order->icon->setmouseDownFunction([&](SDL_MouseButtonEvent &mouse) {
            order->icon->setColor({255, 255, 255, 255});
            order->text->setForeGroundColor({255, 255, 255, 255});
            user->icon->setColor({180, 180, 180, 255});
            user->text->setForeGroundColor({180, 180, 180, 255});
            menu->icon->setColor({180, 180, 180, 255});
            menu->text->setForeGroundColor({180, 180, 180, 255});
            logout->icon->setColor({180, 180, 180, 255});
            logout->text->setForeGroundColor({180, 180, 180, 255});
            isInMenu = false;
            accountUI->close();
        });
        logout->icon->setmouseDownFunction([&](SDL_MouseButtonEvent &mouse) {
            menu->icon->setColor({255, 255, 255, 255});
            menu->text->setForeGroundColor({255, 255, 255, 255});
            user->icon->setColor({180, 180, 180, 255});
            user->text->setForeGroundColor({180, 180, 180, 255});
            order->icon->setColor({180, 180, 180, 255});
            order->text->setForeGroundColor({180, 180, 180, 255});
            logout->icon->setColor({180, 180, 180, 255});
            logout->text->setForeGroundColor({180, 180, 180, 255});
            isInMenu = true;
            accountUI->close();
            openSignIn = true;
        });
    }  
};

/////////////////////////////////////////////////////////
//
// -> CART CLASS
// -> Just a class for Cart, the one on the RIGHT
//
/////////////////////////////////////////////////////////
class Cart : public Layout::BaseLayout {
public:
    class OrderClass : public Layout::BaseLayout {
    public:
        int row = 0;
        std::shared_ptr<Image> image;
        Text text = Text("", 940, 220, 180, 50);
        Text textPrice = Text("", 940, 250, 180, 50, JDM::getColorFromHexA("dfdfdfff"));
        Image ex = Image("Assets/ImageAsset/Store/Icon/xicon.png", 1090, 0, 25, 25);
        OrderClass(const std::string &path, const std::string &tex, const std::string textP = 0, int row = 0) {
            this->row = row;
            text.setText(tex); text.setHalign(JDM::Font::LEFT);
            text.setFontSize(8); text.setFontRegular(BoldFont);
            text.setY(220 + (row * 50));

            textPrice.setHalign(JDM::Font::LEFT); textPrice.setFontSize(7);
            textPrice.setFontRegular(BoldFont); textPrice.setY(240 + (row * 50));
            ex.setY(text.getY() + 20);

            ex.setmouseDownFunction([&](SDL_MouseButtonEvent &mouse) { removeOrder(this->row); this->text.setText("None"); });
            image = std::make_shared<Image>(path, 880+5, 230 + (row * 50)+5, 40, 40);
            this->addComponents(image);
        }
        const bool mouseDownComp(SDL_MouseButtonEvent &mouse) { return ex.mouseDownComp(mouse); }
        const void update() {
            text.update(); textPrice.update();
            ex.update(); Layout::BaseLayout::update();
        }
        const void renderComp() {
            text.renderComp(); textPrice.renderComp();
            ex.renderComp(); Layout::BaseLayout::renderComp();
            SDL_SetRenderDrawColor(JDM::renderer, 0x6d, 0x6d, 0x6d, 255);
            SDL_RenderDrawLineF(JDM::renderer, 940, text.getY() + 50, 940 + 180, text.getY() + 50);
        }
    };

    class TwoText : public Text {
    public:
        Text text = Text("", 880, 570, 240, 50);
        TwoText(const std::string &text1, const std::string &text2, double y, int fontSize = 10, ColorRGBA color = {255, 255, 255, 255})
            : Text(text1, 880, y, 240, 50, color) {
            this->setFontSize(fontSize);
            this->setHalign(JDM::Font::LEFT);
            this->setFontRegular(BoldFont);

            text.setY(y);
            text.setText(text2);
            text.setFontSize(fontSize);
            text.setForeGroundColor(color);
            text.setFontRegular(BoldFont);
            text.setHalign(JDM::Font::RIGHT);
        }
        const void update() { Text::update(); text.update(); }
        const void renderComp() { Text::renderComp(); text.renderComp(); }
    };
    std::shared_ptr<Image> cartField = std::make_shared<Image>(RoundedImage, 850, 10, 300, 680, JDM::getColorFromHexA("4d4d4dff"), 30);
    std::shared_ptr<Image> delieveryLocationField = std::make_shared<Image>(RoundedImage, 860, 20, 280, 100, JDM::getColorFromHexA("6d6d6dff"), 30);
    std::shared_ptr<Button> confirmOrder = std::make_shared<Button>("Confirm Order", RoundedImage,
        880, 670-50, 240, 50, JDM::getColorFromHexA("ffffffff"), JDM::getColorFromHexA("202020ff"),
        JDM::getColorFromHexA("101010ff"));

    Text text = Text("DELIEVERY ADDRESS", 880, 30, 240, 30, {255, 255, 255, 255}, 10, JDM::Font::LEFT);
    Text location = Text("", 910, 60, 210, 30, JDM::getColorFromHexA("dcdcdcff"), 8, JDM::Font::LEFT);
    Image locationIcon = Image("Assets/ImageAsset/Store/Icon/locationicon.png", 885, 65, 20, 20, JDM::getColorFromHexA("dcdcdcff"));

    Image cartIcon = Image("Assets/ImageAsset/Store/Icon/carticon.png", 880, 140, 30, 30, JDM::getColorFromHexA("dcdcdcff"));
    Text cart = Text("Cart", 920, 140, 210, 30, {255, 255, 255, 255}, 10, JDM::Font::LEFT);

    Image backGroundButt = Image(RoundedImage, 880-4, 190-4, 248, 38, JDM::getColorFromHexA("6d6d6dff"), 20);
    std::shared_ptr<Label> delievery = std::make_shared<Label>("Delievery", RoundedImage, 880, 190, 240/3.f, 30, JDM::getColorFromHexA("ffffffff"), JDM::getColorFromHexA("b82f2dff"), 20, 8);
    std::shared_ptr<Label> dineIn = std::make_shared<Label>("Dine In", RoundedImage, 240/3.f+880, 190, 240/3.f, 30, JDM::getColorFromHexA("ffffffaa"), JDM::getColorFromHexA("b82f2d00"), 20, 8);
    std::shared_ptr<Label> takeOut = std::make_shared<Label>("Take Out", RoundedImage, 240/3.f*2+880, 190, 240/3.f, 30, JDM::getColorFromHexA("ffffffaa"), JDM::getColorFromHexA("b82f2d00"), 20, 8);

    OrderClass first = OrderClass(CircleImage, "None", "", 0);
    OrderClass second = OrderClass(CircleImage, "None", "", 1);
    OrderClass third = OrderClass(CircleImage, "None", "", 2);
    OrderClass fourth = OrderClass(CircleImage, "None", "", 3);

    double oldPrice = 0;
    TwoText total = TwoText("TOTAL", "$ 0.00", 560);
    TwoText subTotal = TwoText("Sub Total", "$ 0.00", 470, 8, JDM::getColorFromHexA("dfdfdfff"));
    TwoText delieveryCharge = TwoText("Delievery Charge", "FREE", 500, 8, JDM::getColorFromHexA("dfdfdfff"));

    Cart() {
        confirmOrder->setHoverColor(JDM::getColorFromHexA("151515ff"));
        confirmOrder->setArc(30);
        confirmOrder->setFontSize(10);
        confirmOrder->setFontRegular(BoldFont);
        confirmOrder->setPickOnTop(false);
        confirmOrder->setmouseDownFunction([&](SDL_MouseButtonEvent &mouse) {
            if (orderedOrder()) {
                notif->show("Ordered Successfully!");
            } else notif->show("Ordered Unsuccessfully!");
        });

        text.setFontRegular(SemiBoldFont);
        location.setText(allUser.at(currentUser).location);
        location.setFontRegular(SemiBoldFont);
        cart.setFontRegular(SemiBoldFont);

        delievery->setFontRegular(BoldFont);
        delievery->setmouseUpFunction([&](SDL_MouseButtonEvent &event) {
            dineIn->setAImage(0);
            dineIn->setAForeGround(0xaa);
            delievery->setAImage(0xff);
            delievery->setAForeGround(0xff);
            takeOut->setAImage(0);
            takeOut->setAForeGround(0xaa);
        });

        dineIn->setFontRegular(BoldFont);
        dineIn->setmouseUpFunction([&](SDL_MouseButtonEvent &event) {
            dineIn->setAImage(0xff);
            dineIn->setAForeGround(0xff);
            delievery->setAImage(0);
            delievery->setAForeGround(0xaa);
            takeOut->setAImage(0);
            takeOut->setAForeGround(0xaa);
        });

        takeOut->setFontRegular(BoldFont);
        takeOut->setmouseUpFunction([&](SDL_MouseButtonEvent &event) {
            dineIn->setAImage(0);
            dineIn->setAForeGround(0xaa);
            delievery->setAImage(0);
            delievery->setAForeGround(0xaa);
            takeOut->setAImage(0xff);
            takeOut->setAForeGround(0xff);
        });

        backGroundButt.setLineWidth(2);
        this->addComponents(cartField);
        this->addComponents(delieveryLocationField);
        this->addComponents(confirmOrder);
        this->addComponents(std::make_shared<Canvas::Circle>(825, 425, 50, 50, JDM::getColorFromHexA("1d1d1dff")));
        this->addComponents(std::make_shared<Canvas::Circle>(1125, 425, 50, 50, JDM::getColorFromHexA("1d1d1dff")));
    }
    const bool mouseDownComp(SDL_MouseButtonEvent &mouse) {
        dineIn->mouseDownComp(mouse);
        delievery->mouseDownComp(mouse);
        takeOut->mouseDownComp(mouse);
        if (first.text.getText() != "None") first.mouseDownComp(mouse);
        if (second.text.getText() != "None") second.mouseDownComp(mouse);
        if (third.text.getText() != "None") third.mouseDownComp(mouse);
        if (fourth.text.getText() != "None") fourth.mouseDownComp(mouse);
        return Layout::BaseLayout::mouseDownComp(mouse);
    }
    const void mouseUpComp(SDL_MouseButtonEvent &mouse) {
        dineIn->mouseUpComp(mouse);
        delievery->mouseUpComp(mouse);
        takeOut->mouseUpComp(mouse);
        return Layout::BaseLayout::mouseUpComp(mouse);
    }
    const void update() {
        int number = 0;
        if (changed) {

            // THIS TRICKED IS UGLY, BUT TOO LAZY TO FIX (AGAIN)

        first.text.setText("None");
        second.text.setText("None");
        third.text.setText("None");
        fourth.text.setText("None");
        for (int i = allUser.at(currentUser).currentOrder.size() - 1; i >= 0; i--) {
            if (number >= 4) break;
            Order order = *allUser.at(currentUser).currentOrder[i];
            std::stringstream ss;
            ss << "$ " << std::fixed << std::setprecision(2) << order.price;
            switch (number) {
                case 0:
                    first.image->setSource(order.filePath);
                    first.textPrice.setText(ss.str());
                    first.text.setText(order.nameOrder);
                    break;
                case 1:
                    second.image->setSource(order.filePath);
                    second.textPrice.setText(ss.str());
                    second.text.setText(order.nameOrder);
                    break;
                case 2:
                    third.image->setSource(order.filePath);
                    third.textPrice.setText(ss.str());
                    third.text.setText(order.nameOrder);
                    break;
                case 3:
                    fourth.image->setSource(order.filePath);
                    fourth.textPrice.setText(ss.str());
                    fourth.text.setText(order.nameOrder);
                    break;
            }
            number++;
        }}
        changed = false;
        if (location.getText() != allUser.at(currentUser).location)
            location.setText(allUser.at(currentUser).location);

        Layout::BaseLayout::update(); text.update();
        locationIcon.update(); location.update();
        cartIcon.update(); cart.update();
        backGroundButt.update(); delievery->update();
        dineIn->update(); takeOut->update();
        first.update(); second.update();
        third.update(); fourth.update();

        if (oldPrice != totalValueOfOrder) {
            std::stringstream ss;
            ss << "$ " << std::fixed << std::setprecision(2) << totalValueOfOrder;
            total.text.setText(ss.str());
            subTotal.text.setText(ss.str());
            oldPrice = totalValueOfOrder;
        }
        total.update(); subTotal.update(); delieveryCharge.update();
    }

    const void renderComp() {
        Layout::BaseLayout::renderComp();
        text.renderComp(); locationIcon.renderComp(); location.renderComp();
        cartIcon.renderComp(); cart.renderComp();
        backGroundButt.renderComp(); delievery->renderComp();
        dineIn->renderComp(); takeOut->renderComp();
        if (first.text.getText() != "None") first.renderComp();
        if (second.text.getText() != "None") second.renderComp();
        if (third.text.getText() != "None") third.renderComp();
        if (fourth.text.getText() != "None") fourth.renderComp();
        total.renderComp(); subTotal.renderComp(); delieveryCharge.renderComp();
        SDL_SetRenderDrawColor(JDM::renderer, 0x6d, 0x6d, 0x6d, 255);
        SDL_RenderDrawLineF(JDM::renderer, total.getX(), total.getY() - 10, total.getX() + total.getWidth(), total.getY() - 10);
    }
};

/////////////////////////////////////////////////////////
//
// -> SIGNUP  CLASS
// -> Just a class for Login Screen
//
/////////////////////////////////////////////////////////
class SignInUp : public Layout::BaseLayout {
public:
    bool lastCall = true;
    std::shared_ptr<Image> background = std::make_shared<Image>( DefaultImage, 0, 0, 1200, 700, JDM::getColorFromHexA("000000cc"));
    std::shared_ptr<Image> image = std::make_shared<Image>( DefaultImage, 0, 10, 480, 680, JDM::getColorFromHexA("4f4f4fff"));
    std::shared_ptr<Image> burger = std::make_shared<Image>( "Assets/ImageAsset/Store/burger.png", -480, 10, 960, 680);

    std::shared_ptr<Image> icon = std::make_shared<Image>( "Assets/ImageAsset/Store/Icon/icon.png", 990, 40, 100, 100);
    std::shared_ptr<Label> welcome = std::make_shared<Label>("Welcome", DefaultImage, 0, 40, 840, 100, JDM::getColorFromHexA("ffffffff"), JDM::getColorFromHexA("EEBC1Dff"), 30, 30, JDM::Font::RIGHT);
    
    std::shared_ptr<Text> expresso = std::make_shared<Text>( "EXPRESSO YOURSELF", 530, 160, 400, 50, JDM::getColorFromHexA("dfdfdfff"), 30, JDM::Font::LEFT);
    std::shared_ptr<Text> expressoDetails = std::make_shared<Text>( "\"Flavour Fusion: Where Palates Ignite with Delight\"", 530, 190, 400, 50, JDM::getColorFromHexA("dfdfdfff"), 15, JDM::Font::LEFT);

    std::shared_ptr<Text> motto1 = std::make_shared<Text>( "THE FASTEST", 580, 260, 620, 76.67, JDM::getColorFromHexA("ffffffff"), 35);
    std::shared_ptr<Text> motto2 = std::make_shared<Text>( "DELIEVERY AND", 580, 336.67, 620, 76.67, JDM::getColorFromHexA("ffffffff"), 35);
    std::shared_ptr<Text> motto3 = std::make_shared<Text>( "EASY PICK UP", 580, 413.34, 620, 76.67, JDM::getColorFromHexA("ffffffff"), 35);
    
    std::shared_ptr<Image> mottoRect = std::make_shared<Image>( DefaultImage, 580, 250, 620, 250, JDM::getColorFromHexA("EEBC1Dff"));
    
    std::shared_ptr<TextInput> name = std::make_shared<TextInput>( "", 500, 520, 340, 50,
        JDM::getColorFromHexA("dfdfdfff"),
        JDM::getColorFromHexA("2d2d2dff"),
        "Assets/ImageAsset/Store/Icon/accounticon.png");

    std::shared_ptr<TextInput> location = std::make_shared<TextInput>("Unknown", 500, 575, 680, 50,
        JDM::getColorFromHexA("dfdfdfff"),
        JDM::getColorFromHexA("2d2d2dff"),
        "Assets/ImageAsset/Store/Icon/locationicon.png");
    
    std::shared_ptr<TextInput> budget = std::make_shared<TextInput>("0", 840, 520, 340, 50,
        JDM::getColorFromHexA("dfdfdfff"),
        JDM::getColorFromHexA("2d2d2dff"),
        "Assets/ImageAsset/Store/Icon/budget.png");

    std::shared_ptr<Button> loginButton = std::make_shared<Button>("Login / Register", RoundedImage,500, 630, 680, 50,
        JDM::getColorFromHexA("ffffffff"),
        JDM::getColorFromHexA("202020ff"),
        JDM::getColorFromHexA("101010ff"));

    SignInUp() {
        loginButton->setHoverColor(JDM::getColorFromHexA("151515ff"));
        loginButton->setArc(30);
        loginButton->setFontSize(10);
        loginButton->setFontRegular(BoldFont);
        loginButton->setPickOnTop(false);

        loginButton->setmouseDownFunction([&](SDL_MouseButtonEvent &mouse) {
            if (name->getText() != "" && location->getText() != "" && budget->getText() != "") {
                currentUser = name->getText();
                if (!checkIfAccountisAlreadyExist(name->getText())) {
                    currentUser = name->getText();
                    allUser[name->getText()] = {
                        name->getText(),
                        location->getText(),
                        std::stof(budget->getText())
                    };
                }
                openSignIn = false;
                this->closeAnimation();
            }
        });

        name->setArc(30); name->setFontRegular(SemiBoldFont);
        name->setFontSize(8); name->setLineWidth(5);
        name->setPickOnTop(false);

        location->setArc(30); location->setFontRegular(SemiBoldFont);
        location->setFontSize(8); location->setLineWidth(5);
        location->setPickOnTop(false);

        budget->setArc(30); budget->setFontRegular(SemiBoldFont);
        budget->setFontSize(8); budget->setLineWidth(5);
        budget->setPickOnTop(false);

        expresso->setFontRegular(SemiBoldFont);
        expressoDetails->setFontRegular(SemiBoldFont);

        image->setArcTR(30); image->setArcBR(30);
        mottoRect->setArcTL(30); mottoRect->setArcBL(30);
        welcome->setFontRegular(BoldFont); welcome->setPaddingWidth(80);
        motto1->setFontRegular(BoldFont); motto2->setFontRegular(BoldFont); motto3->setFontRegular(BoldFont);

        this->addComponents(background);
        this->addComponents(icon);
        this->addComponents(welcome);
        this->addComponents(image);
        this->addComponents(burger);

        this->addComponents(loginButton);
        this->addComponents(name);
        this->addComponents(location);
        this->addComponents(budget);
        this->addComponents(expresso);
        this->addComponents(expressoDetails);
        this->addComponents(mottoRect);
        this->addComponents(motto1);
        this->addComponents(motto2);
        this->addComponents(motto3);
    }

    const void update() {
        Layout::BaseLayout::update();
        if (openSignIn != lastCall) {
            lastCall = openSignIn;
            if (openSignIn) openAnimation();
            else closeAnimation();
        }
    }

    const void closeAnimation() {
        // ANIMATION ON LOGIN CLOSE
        changed = true;
        accessible = true;
        updateHistory = true;
        getTotalValue();
        notif->show("Login successfully");

        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(image->getPointerX(), image->getX()-1200, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(burger->getPointerX(), burger->getX()-1200, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(welcome->getPointerX(), welcome->getX()-1200, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(icon->getPointerX(), icon->getX()+800, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(expresso->getPointerX(), expresso->getX()+800, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(expressoDetails->getPointerX(), expressoDetails->getX()+800, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(motto1->getPointerX(), motto1->getX()+800, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(motto2->getPointerX(), motto2->getX()+800, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(motto3->getPointerX(), motto3->getX()+800, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(mottoRect->getPointerX(), mottoRect->getX()+800, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(loginButton->getPointerX(), loginButton->getX()+800, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(budget->getPointerX(), budget->getX()+800, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(location->getPointerX(), location->getX()+800, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(name->getPointerX(), name->getX()+800, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<uint8_t>>(background->getPointerAImage(), 0, 1, true));
    }
    const void openAnimation() {
        // ANIMATION ON LOGIN OPEN
        accessible = false;
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(image->getPointerX(), 0, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(burger->getPointerX(), -480, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(welcome->getPointerX(), 40, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(icon->getPointerX(), 990, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(expresso->getPointerX(), 530, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(expressoDetails->getPointerX(), 530, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(motto1->getPointerX(), 580, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(motto2->getPointerX(), 580, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(motto3->getPointerX(), 580, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(mottoRect->getPointerX(), 580, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(loginButton->getPointerX(), 500, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(budget->getPointerX(), 840, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(location->getPointerX(), 500, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<double>>(name->getPointerX(), 500, 0.5, true));
        JDM::Window::addStartAnimation(std::make_shared<Animation<uint8_t>>(background->getPointerAImage(), 0xcc, 0.1, true));
    }
};

/////////////////////////////////////////////////////////
//
// -> MAIN STORE CLASS
// -> A class for main Store, soon i will create a Screenmanager, this is ugly
//
/////////////////////////////////////////////////////////
class Store : public Window {
public:
    
    std::shared_ptr<Image> searchButton = std::make_shared<Image>(
        "Assets/ImageAsset/Store/Icon/searchicon.png", 770, 20, 40, 40);
    std::shared_ptr<Layout::BaseLayout> mainMenu = std::make_shared<Layout::BaseLayout>();
    std::shared_ptr<SignInUp> signUp = std::make_shared<SignInUp>();

public:
    Store() : Window("Store", JDM_UNDEFINED_POS, JDM_UNDEFINED_POS, 1200, 700, JDM::getColorFromHex("1d1d1d")) {
        this->setIcon("Assets/ImageAsset/Store/Icon/icon.png");
        searchBox->setArc(10);
        searchBox->setColor(JDM::getColorFromHexA("2d2d2dff"));
        searchBox->setForeGroundColor(JDM::getColorFromHexA("dfdfdfff"));
        searchBox->setFontRegular(SemiBoldFont);
        searchBox->setFontSize(8);
        searchBox->setLineWidth(5);

        searchButton->setmouseDownFunction([&](SDL_MouseButtonEvent &mouse) { updateDishes = true; });
        mainMenu->isAccessible = false;
        mainMenu->addComponents(std::make_shared<Categories>());
        mainMenu->addComponents(std::make_shared<Dishes>());
        mainMenu->addComponents(std::make_shared<DashBoard>());
        mainMenu->addComponents(std::make_shared<Cart>());
        mainMenu->addComponents(searchBox);
        mainMenu->addComponents(searchButton);

        this->addComponents(mainMenu);
        this->addComponents(signUp);

        notif = std::make_shared<Notification>();
        this->addComponents(notif);
    }
    void update() { mainMenu->isAccessible = accessible; }

};

int main(int argv, char **argc) {
    loadJsonAllUser();
    std::make_shared<Store>()->run();
    saveJsonAllUser();

    return 0;
}