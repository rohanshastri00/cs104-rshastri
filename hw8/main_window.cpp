#include "main_window.h"
#include <sstream>

MainWindow::MainWindow(MyDataStore* dsPTR)
{
    showAmazonWidget = new QWidget();
	dsPTR_ = dsPTR;

    loginLayout = new QVBoxLayout();
    usernameLayout = new QHBoxLayout();
    passwordLayout = new QHBoxLayout();
    loginAccessLayout = new QHBoxLayout();

    loginScreen = new QWidget();
    username = new QWidget(); 
    password = new QWidget();
    loginWidget = new QWidget();

    loginLayout->addLayout(usernameLayout);
    loginLayout->addLayout(passwordLayout);
    loginLayout->addLayout(loginAccessLayout);
    loginScreen->setLayout(loginLayout);


    usernameLabel = new QLabel("Username: ");;
    passwordLabel = new QLabel("Password: ");
    usernameInput = new QLineEdit();
    passwordInput = new QLineEdit();
    loginButton = new QPushButton("Login");
    newUserButton =  new QPushButton ("New User");
    quitLoginWindow = new QPushButton("Quit Login");


    loginScreen->setWindowTitle("Amazon Login");
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameInput);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordInput);
    passwordInput->setEchoMode(QLineEdit::Password);
    loginAccessLayout->addWidget(loginButton);
    loginAccessLayout->addWidget(newUserButton);
    loginAccessLayout->addWidget(quitLoginWindow);

    connect(loginButton, SIGNAL(clicked()), this, SLOT(loginButtonClicked()));
    connect(quitLoginWindow, SIGNAL(clicked()), this, SLOT(close()));
    connect(newUserButton, SIGNAL(clicked()), this, SLOT(createAccount()));

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


    openProdRecButton = new QPushButton("Recommendations");
    leftLayout->addWidget(openProdRecButton);
    connect(openProdRecButton, SIGNAL(clicked()), this, SLOT(displayRecsClicked()));

    product_rec_popup = new QWidget();
    prod_recLayout = new QVBoxLayout();
    product_rec_popup->setLayout(prod_recLayout);
    product_rec_popup->setWindowTitle("Recommendations");

    prodRecLabel = new QLabel("Product Recommendations: ");
    prod_recLayout->addWidget(prodRecLabel);

    prodRecList =  new QListWidget();
    prod_recLayout->addWidget(prodRecList);

    closeProdRecButton = new QPushButton("Done");
    prod_recLayout->addWidget(closeProdRecButton);

    connect(closeProdRecButton, SIGNAL(clicked()), this, SLOT(hideRecButton()));

    product_rec_popup->hide();

	// Set overall layout
	//setLayout(amazonLayout);
    setLayout(loginLayout);
	connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

	//initialize user
}


void MainWindow::loginButtonClicked()
{
	string username = usernameInput->text().toStdString();
	map<string, User*> users = dsPTR_->getUserDatabase();
	map<string, User*>::iterator user_it = users.find(username);

	QMessageBox msgBox;

	if (user_it == users.end()) { 
		msgBox.setWindowTitle("Username Error");
		msgBox.setText("Username does not exist.");
		msgBox.exec();
		usernameInput->clear();
		passwordInput->clear();
	} else {
		unsigned long long current_password = hash(passwordInput->text().toStdString());
		unsigned long long user_password = (user_it->second)->getPassword();
		//passwords match
		if (current_password == user_password) {
			showAmazonWindow();
			usernameInput->clear();
			passwordInput->clear();
		} else {
			msgBox.setWindowTitle("Incorrect Password");
			msgBox.setText("Password does not match username. Try again.");
			msgBox.exec();
			passwordInput->clear();

		}
	}
}

unsigned long long MainWindow::hash(string password)
{
	unsigned long long hash = 0;
	int count = 0;
	for (int i = password.size() - 1; i >= 0; i--) {
		hash += ((int)password[i] * (unsigned long long)pow(128, count));
		++count;
	}

	unsigned int arr[4];
	arr[3] = hash % 65521;
	hash = hash/65521;
	arr[2] = hash % 65521;
	hash = hash/65521;
	arr[1] = hash % 65521;
	hash = hash/65521;
	arr[0] = hash % 65521;

	unsigned long long sum =  arr[3] * 4625 + arr[2] * 65169 + arr[1] * 35511 + arr[0] * 45912;
	hash = sum % 65521;
	return hash;

}

void MainWindow::createAccount() 
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("Error while creating account");
	string username = usernameInput->text().toStdString();


	if (usernameInput->text().isEmpty() || passwordInput->text().isEmpty()) {
		msgBox.setText("Please fill in the required fields");
		msgBox.exec();
	}
	//username exists
	else if (dsPTR_->userExists(username)) {
		msgBox.setText("Username already exists");
		msgBox.exec();
	}
	else if (passwordInput->text().toStdString().size() > 8) {
		msgBox.setText("Password must be less than 8 characters");
		msgBox.exec();
	}
	else {
		unsigned long long user_password = hash(passwordInput->text().toStdString());
		User* u = new User(username, 100.0, 1, user_password);
		dsPTR_->addUser(u);
		QString qstr = QString::fromStdString(username);
		userDropDown->addItem(qstr);
		showAmazonWindow();
		passwordInput->clear();
		usernameInput->clear();
	}
}

void MainWindow::showAmazonWindow()
{
	showAmazonWidget->setLayout(amazonLayout);
	loginScreen->hide();
	showAmazonWidget->show();
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


void MainWindow::displayReviewsClicked(int index)
{
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
  	if (myCartList->count() < 1) { return; }
 	QString qCurrUser = userDropDown->currentText();
  	string currUser = qCurrUser.toStdString();
  	//get the user + cart
  	User* u = dsPTR_->getCurrentUser(currUser);
  	vector<Product*> current_cart = dsPTR_->getCart(currUser);
  	//now taking from GUI
  	QList<QListWidgetItem*> cartItems = myCartList->selectedItems();
  	QString current_product = myCartList->currentItem()->text();
  	string productname = current_product.toStdString();
  	//Product* p = dsPTR_->findProduct(productname);
  	dsPTR_->removeFromCart(u, productname);
  	foreach(QListWidgetItem* item, cartItems) {
  		//string str = item->text().toStdString();
  		delete myCartList->takeItem(myCartList->row(item));
  	}
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


void MainWindow::displayRecsClicked()
{
	product_rec_popup->show();
	makeRecs();
}

void MainWindow::makeRecs()
{
	prodRecList->clear();
	string output_filename = "rec.txt";
	ofstream ofile(output_filename.c_str());
	QString qCurrUser = userDropDown->currentText();
  	string currUser = qCurrUser.toStdString();
  	ofile << currUser << endl;

  	typedef std::pair<string, double> nameAndScore;
  	vector <nameAndScore> rec_products = dsPTR_->makeSuggestion(currUser);
  	
  	ProdRec<nameAndScore> rating_comp;
   	mergeSort< nameAndScore, ProdRec<nameAndScore> >(rec_products, rating_comp);

   	for (unsigned int i = 0; i < rec_products.size();i++) {
   		QString qprod = QString::number(rec_products[i].second, 'f', 2) + QString::fromStdString(" ") 
   		+ QString::fromStdString(rec_products[i].first);
   		prodRecList->addItem(qprod);
   		ofile << fixed << setprecision(2) << rec_products[i].second << " " << rec_products[i].first << endl;
   	}

}

void MainWindow::hideRecButton()
{
	product_rec_popup->hide();
}