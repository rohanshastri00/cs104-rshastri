#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QComboBox>
#include <QRadioButton>
#include "mydatastore.h"
#include <sstream>
#include <QFileDialog>
#include <QApplication>
#include <string>
#include <vector>
#include <fstream>

class MainWindow : public QWidget
{
  Q_OBJECT
public:
  MainWindow(MyDataStore* ds);
  //~MainWindow();
private slots:

  void displaySearchResults();

  void searchButtonClicked();

  void sortAlphabeticallyButtonClicked();
  void sortRatingButtonClicked();

  void displayReviewsClicked(int index); 
  void sortDateButtonClicked();

  void addToCartButtonClicked();
  void viewCartButtonClicked();
  void buyCartButtonClicked();
  void closePopupButtonClicked();
  void removeProductButtonClicked();

  void addReviewButtonClicked();
  void saveButtonClicked();
  void quit();

private:
    // // UI

    // Main Layouts
    QHBoxLayout* amazonLayout;

    QVBoxLayout* leftLayout;
      // Search
      QHBoxLayout* searchLayout;
      QLineEdit* keywordSearchInput;
      QPushButton* searchButton;
      QListWidget* productListWidget;
      // andOr
      QHBoxLayout* andOr;
      QRadioButton* andButton;
      QRadioButton* orButton; 
      QLabel* sortLabel;
      QPushButton* sortAlphabeticalButton;
      QPushButton* sortRatingButton;
      // Cart Functionality
      QHBoxLayout* cartButtonLayout;
      QPushButton* addToCartButton;
      QPushButton* viewCartButton;

    QVBoxLayout* rightLayout;
      // Users
      QHBoxLayout* usersLayout;
      QLabel* UsersLabel;
      QComboBox* userDropDown;
      // Reviews
      QHBoxLayout* reviewLayout;
      QLabel* reviewLabel;
      QLabel* sortReviewLabel;
      QPushButton* sortReviewsbyDateButton;
      QListWidget* reviewListWidget;
      // Rating
      QHBoxLayout* ratingLayout;
      QLabel* ratingLabel;
      QLineEdit* ratingTextInput;
      // Date
      QHBoxLayout* dateLayout;
      QLabel* dateLabel;
      QLineEdit* dateText1;
      QLineEdit* dateText2;
      QLineEdit* dateText3;
      //  Review Text
      QHBoxLayout* reviewTextLayout;
      QLabel* reviewTextLabel;
      QLineEdit* reviewTextInput;
      // Right Bottom buttons;
      QHBoxLayout* rightBottom;
      QPushButton* addReviewButton;
      QPushButton* saveButton;
      QPushButton* quitButton;

      //Cart Window
      QWidget* popup;

      QHBoxLayout* cartLayout;
      QVBoxLayout* leftCartLayout;
        QLabel* cartLabel;
        QListWidget* myCartList;
      QVBoxLayout* rightCartLayout;
        QPushButton* buyCartButton;
        QPushButton* removeProductButton;
        QPushButton* closePopupButton;


      // Private
      MyDataStore* dsPTR_;
      vector<Product*>hits;

      vector<User*> mwUsers;
      //User* current;

};

