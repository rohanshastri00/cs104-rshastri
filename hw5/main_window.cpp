#include "main_window.h"
#include <sstream>

MainWindow::MainWindow(MyDataStore* dsPTR)
{
	dsPTR_ = dsPTR;

	// Title
	setWindowTitle("Amazon");


	// Overall layout
	amazonLayout = new QHBoxLayout();
	leftLayout = new QVBoxLayout();
	rightLayout = new QVBoxLayout();

	amazonLayout->addLayout(leftLayout);
	amazonLayout->addLayout(rightLayout);

	// // Search layout
	searchLayout = new QHBoxLayout();
	leftLayout->addLayout(searchLayout);

	keywordSearchInput =  new QLineEdit();
	searchLayout->addWidget(keywordSearchInput);

	searchButton = new QPushButton("Search");
	connect(searchButton, SIGNAL(clicked()), this, SLOT(searchButtonClicked()));
	searchLayout->addWidget(searchButton);

		andOr = new QHBoxLayout();
		leftLayout->addLayout(andOr);
		    andButton = new QRadioButton("AND");
		    orButton = new QRadioButton("OR"); 
		    sortLabel = new QLabel("Sort by: ");
		    sortAlphabeticalButton = new QPushButton("Alphabetical");
		    connect(sortAlphabeticalButton, SIGNAL(clicked()), this, SLOT(sortAlphabeticallyButtonClicked()));
		    sortRatingButton = new QPushButton("Rating");
		    connect(sortRatingButton, SIGNAL(clicked()), this, SLOT(sortRatingButtonClicked()));	    
		    andOr->addWidget(andButton);
		    andOr->addWidget(orButton);
		    andOr->addWidget(sortLabel);
		    andOr->addWidget(sortAlphabeticalButton);
		    andOr->addWidget(sortRatingButton);

	productListWidget = new QListWidget();
	connect(productListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(displayReviewsClicked(int)));
	leftLayout->addWidget(productListWidget);

	//Cart Functionality
	cartButtonLayout = new QHBoxLayout();
	leftLayout->addLayout(cartButtonLayout);
	  	addToCartButton = new QPushButton("Add to Cart");
	  	connect(addToCartButton, SIGNAL(clicked()), this, SLOT(addToCartButtonClicked()));
	  	viewCartButton = new QPushButton("View Cart");
		connect(viewCartButton, SIGNAL(clicked()), this, SLOT(viewCartButtonClicked()));
	   	cartButtonLayout->addWidget(addToCartButton);
	   	cartButtonLayout->addWidget(viewCartButton);


    // Users
	usersLayout = new QHBoxLayout();
	rightLayout->addLayout(usersLayout);
	    UsersLabel = new QLabel("Users: ");
	    userDropDown = new QComboBox();
	    mwUsers = dsPTR_->getUserVector();
	    for (unsigned int i = 0; i < mwUsers.size();i++)
	    {
	    	string current = mwUsers[i]->getName();
	    	QString qCurrent = QString::fromStdString(current);
	    	userDropDown->addItem(qCurrent);
	    }
	  	usersLayout->addWidget(UsersLabel);
	  	usersLayout->addWidget(userDropDown);

	// Reviews
	reviewLayout = new QHBoxLayout();
	rightLayout->addLayout(reviewLayout);
	  	sortReviewLabel = new QLabel("Sort by: ");
      	sortReviewsbyDateButton = new QPushButton("Date");
      	connect(sortReviewsbyDateButton, SIGNAL(clicked()), this, SLOT(sortDateButtonClicked()));

      	
		reviewLabel = new QLabel("Reviews: ");
		reviewListWidget = new QListWidget();
		reviewLayout->addWidget(reviewLabel);
		reviewLayout->addWidget(sortReviewLabel);
		reviewLayout->addWidget(sortReviewsbyDateButton);
	rightLayout->addWidget(reviewListWidget);

	// Rating
	ratingLayout = new QHBoxLayout();
	rightLayout->addLayout(ratingLayout);
		ratingLabel = new QLabel("Rating: ");
		ratingTextInput = new QLineEdit();
		ratingLayout->addWidget(ratingLabel);
		ratingLayout->addWidget(ratingTextInput);

	// Date
	dateLayout = new QHBoxLayout();
	rightLayout->addLayout(dateLayout);
		dateLabel = new QLabel("Date(YYYY-MM-DD): ");
		dateText1 = new QLineEdit();
		dateText2 = new QLineEdit();
		dateText3 = new QLineEdit();
		dateLayout->addWidget(dateLabel);
		dateLayout->addWidget(dateText1);
		dateLayout->addWidget(dateText2);
		dateLayout->addWidget(dateText3);

	// Review text
	reviewTextLayout = new QHBoxLayout();
	rightLayout->addLayout(reviewTextLayout);
		reviewTextLabel = new QLabel("Review text: ");
		reviewTextInput = new QLineEdit();
		reviewTextLayout->addWidget(reviewTextLabel);
		reviewTextLayout->addWidget(reviewTextInput);

	//Right bottom buttons

	rightBottom = new QHBoxLayout();
	rightLayout->addLayout(rightBottom);
		addReviewButton = new QPushButton("Add Review");
		connect(addReviewButton, SIGNAL(clicked()), this, SLOT(addReviewButtonClicked()));
		saveButton = new QPushButton("Save");
		connect(saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));
		quitButton = new QPushButton("Quit");

		rightBottom->addWidget(addReviewButton);
		rightBottom->addWidget(saveButton);
		rightBottom->addWidget(quitButton);

	// Make it so image and name are at the top
	leftLayout->addStretch();
	rightLayout->addStretch();

	popup = new QWidget();
	cartLayout = new QHBoxLayout();
    leftCartLayout = new QVBoxLayout();
    	cartLabel = new QLabel(" ");
        myCartList = new QListWidget();
    rightCartLayout = new QVBoxLayout();
        buyCartButton = new QPushButton("Buy Cart");
        connect(buyCartButton, SIGNAL(clicked()), this, SLOT(buyCartButtonClicked()));
        removeProductButton = new QPushButton("Remove from Cart");
        connect(removeProductButton, SIGNAL(clicked()), this, SLOT(removeProductButtonClicked()));
        closePopupButton = new QPushButton("Close Cart Window");
        connect(closePopupButton, SIGNAL(clicked()), this, SLOT(closePopupButtonClicked()));


	// Set overall layout
	setLayout(amazonLayout);
	connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

	//initialize user
}

void MainWindow::displaySearchResults(){

	for (unsigned int i = 0; i < hits.size(); i++){
		// Name and Price
		string prodName = hits[i]->getName();
		double price = hits[i]->getPrice();
		ostringstream s;
		s << price;
		string price_str = s.str();

		// Quantity
		int qty = hits[i]->getQty();
		ostringstream q;
		q << qty;
		string qty_str = q.str();

		// Rating
		double avgRating = hits[i]->getAvgRating();
		ostringstream r;
		r << avgRating;
		string rating_str = r.str();

		string total = "Price: " + price_str + "		" + "Qty: " + 
		qty_str + "	" + "Rating: ";

		QString qtotal = QString::fromStdString(prodName+'\n'+ total + rating_str);
		productListWidget->addItem(qtotal);
	}
}

void MainWindow::searchButtonClicked()
{
	hits.clear();
	productListWidget->clear();
	
	// Do nothing if user left at least one input blank
	if(keywordSearchInput->text().isEmpty()){
		return;
	}
	vector<string>terms;
	//create a vector of terms
	string input = convToLower(keywordSearchInput->text().toStdString());

	stringstream ss(input);

	string temp;
	while (ss >> temp){
		terms.push_back(temp);
	}
	//0 is AND, 1 is OR
	if (andButton->isChecked() == false && orButton->isChecked() == false){
		return;
	}
	else if (andButton->isChecked()){
		hits = dsPTR_->search(terms, 0);
	}
	else if (orButton->isChecked()){
		hits = dsPTR_->search(terms, 1);
	}

	displaySearchResults();
}

void MainWindow::sortAlphabeticallyButtonClicked()
{

	AlphabetComp<Product*> alpha;
	mergeSort<Product*, AlphabetComp<Product*> >(hits, alpha);
	productListWidget->clear();

	displaySearchResults();

	reviewListWidget->clear();

}
void MainWindow::sortRatingButtonClicked()
{

	RatingComp<Product*> rate;
	mergeSort<Product*, RatingComp<Product*> >(hits, rate);
	productListWidget->clear();

	displaySearchResults();

	reviewListWidget->clear();
}

void MainWindow::sortDateButtonClicked()
{
	int index = productListWidget->currentRow();
	if (index == -1)
	{
		return;
	}
	Product* p = hits[index];
	vector<Review*> sort = dsPTR_->getReview(p);
	DateComp<Review*> date;
	mergeSort<Review*, DateComp<Review*> >(sort, date);
	//displayReviewsClicked(index);

	//nothing is selected
	if (index == -1)
	{
		return;
	}
	reviewListWidget->clear();
	for (unsigned int i = 0; i < sort.size(); i++){
		ostringstream r;
		r << sort[i]->rating;
		string reviewRating = r.str();
		string full = sort[i]->username + " " + reviewRating + " " + sort[i]->date + " " 
		+ sort[i]->reviewText;
		QString qfull = QString::fromStdString(full);
		reviewListWidget->addItem(qfull);
	}
}



void MainWindow::displayReviewsClicked(int index){
	//nothing is selected
	if (index == -1)
	{
		return;
	}
	reviewListWidget->clear();
	vector<Review*> reviews = dsPTR_->getReview(hits[index]);

	for (unsigned int i = 0; i < reviews.size(); i++){
		ostringstream r;
		r << reviews[i]->rating;
		string reviewRating = r.str();
		string full = reviews[i]->username + " " + reviewRating + " " + reviews[i]->date + " " 
		+ reviews[i]->reviewText;
		QString qfull = QString::fromStdString(full);
		reviewListWidget->addItem(qfull);
	}
}

  void MainWindow::addToCartButtonClicked()
  {
  	QString qCurrUser = userDropDown->currentText();
  	string currUser = qCurrUser.toStdString();

  	int index = productListWidget->currentRow();
  	Product* current_product = hits[index];
  	dsPTR_->addToCart(currUser, current_product);  	
  }


  void MainWindow::viewCartButtonClicked()
  {
  	myCartList->clear();
  	QString qCurrUser = userDropDown->currentText();
  	string currUser = qCurrUser.toStdString();

  	string full = currUser + "'s Cart: ";
  	QString qfull = QString::fromStdString(full);

  	popup->setLayout(cartLayout);

   		leftCartLayout->addWidget(cartLabel);
        leftCartLayout->addWidget(myCartList);
        rightCartLayout->addWidget(buyCartButton);
        rightCartLayout->addWidget(removeProductButton);
        rightCartLayout->addWidget(closePopupButton);
        cartLayout->addLayout(leftCartLayout);
   		cartLayout->addLayout(rightCartLayout);

   		cartLabel->setText(qfull);



  	vector<Product*> currentCart = dsPTR_->getCart(currUser);
  	for (unsigned int i = 0; i < currentCart.size();i++){
  		string temp = currentCart[i]->getName();
  		QString qstr = QString::fromStdString(temp);
  		myCartList->addItem(qstr);
  	}

  	    popup->show();

  }
  void MainWindow::buyCartButtonClicked()
  {
 	QString qCurrUser = userDropDown->currentText();
  	string currUser = qCurrUser.toStdString();
  	dsPTR_->buyCart(currUser);

  	//now reprint cart values
  	myCartList->clear();

  	vector<Product*> currentCart = dsPTR_->getCart(currUser);
  	for (unsigned int i = 0; i < currentCart.size();i++){
  		string temp = currentCart[i]->getName();
  		QString qstr = QString::fromStdString(temp);
  		myCartList->addItem(qstr);
  	}


  }
  void MainWindow::removeProductButtonClicked()
  {
  	if (myCartList->count() < 1)
  	{
  		return;
  	}
 	QString qCurrUser = userDropDown->currentText();
  	string currUser = qCurrUser.toStdString();
  	User* u = dsPTR_->getCurrentUser(currUser);
  	vector<Product*> current_cart = dsPTR_->getCart(currUser);
  	int index = myCartList->currentRow();

  	dsPTR_->removeFromCart(u, current_cart[index]);

  	myCartList->takeItem(index);
  }


  void MainWindow::closePopupButtonClicked()
  {
  		popup->hide();
  }


void MainWindow::addReviewButtonClicked()
{
	//check if any fields are empty
	if (ratingTextInput->text().isEmpty() || !(productListWidget->currentRow() >= 0) ||
		dateText1->text().isEmpty() || dateText2->text().isEmpty() || dateText3->text().isEmpty()
		|| reviewTextInput->text().isEmpty())
	{
		return;
	}
	// Rating
	string rating = ratingTextInput->text().toStdString();
	istringstream rate(rating);
	int intRating = 0;
	rate >> intRating;
	// Date
	string year = dateText1->text().toStdString();
	string month = dateText2->text().toStdString();
	string day = dateText3->text().toStdString();
	string date = year+"-"+month+"-"+day;
	// Text
	string text = reviewTextInput->text().toStdString();
	// Product
	Product* temp = hits[productListWidget->currentRow()];
	string product_text = temp->getName();
	// User
	string user_text = userDropDown->currentText().toStdString();

	Review* new_review = new Review(product_text, intRating, user_text, date, text);
	dsPTR_->addReview(new_review);
	displayReviewsClicked(productListWidget->currentRow());
	ratingTextInput->clear();
	dateText1->clear();
	dateText2->clear();
	dateText3->clear();
	reviewTextInput->clear();

	//update the current products rating
	searchButtonClicked();

}
void MainWindow::saveButtonClicked()
{
	QString filename = QFileDialog::getSaveFileName();
	string sfilename = filename.toStdString();

	ofstream ofile(sfilename.c_str());
	dsPTR_->dump(ofile);
	ofile.close();
}

void MainWindow::quit()
{ }

