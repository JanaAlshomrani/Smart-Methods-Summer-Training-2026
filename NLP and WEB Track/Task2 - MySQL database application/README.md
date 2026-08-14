# Person Status Manager

A simple full-stack web application that allows users to add people to a MySQL database and toggle each person’s status between `0` and `1`.

## Live Website

**Website Link:** [Add your live website link here](PASTE_YOUR_WEBSITE_LINK_HERE)

---

## Features

- Add a new person using a one-line form
- Store name and age data in a MySQL database
- Automatically set each new record’s status to `0`
- Display all saved records in a responsive HTML table
- Toggle a person’s status between:
  - `0` = Inactive
  - `1` = Active
- Update the status on the webpage immediately without reloading the page
- Use prepared statements for inserting data safely
- Use PHP, MySQL, HTML, CSS, and JavaScript

---

## Technologies Used

- **HTML** — webpage structure
- **CSS** — responsive design and colors
- **JavaScript** — immediate status update using `fetch()`
- **PHP** — backend logic and database operations
- **MySQL** — data storage
- **InfinityFree** — website hosting and MySQL database hosting

---

## Project Structure

```text
project-folder/
│
├── index.php       # Main webpage, form, table, insert logic, and toggle logic
├── db.php          # MySQL database connection settings
└── README.md       # Project documentation
```

---

## Database Structure

Database name:

```text
if0_42402863_personsdb
```

Table name:

```text
persons
```

SQL used to create the table:

```sql
CREATE TABLE persons (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    age INT NOT NULL,
    status TINYINT(1) NOT NULL DEFAULT 0
);
```

| Column | Type | Description |
|---|---|---|
| `id` | `INT` | Unique record ID, automatically generated |
| `name` | `VARCHAR(100)` | Person's name |
| `age` | `INT` | Person's age |
| `status` | `TINYINT(1)` | Status value: `0` or `1` |

---

## How It Works

1. The user enters a name and age in the form.
2. PHP validates and inserts the submitted data into the `persons` MySQL table.
3. New records receive a default status of `0`.
4. PHP retrieves all records and displays them in the table.
5. Clicking **Toggle** changes the selected record’s status:
   - `0` becomes `1`
   - `1` becomes `0`
6. JavaScript updates the status badge immediately on the webpage.

---

## Website Screenshot

> Add a screenshot of the completed website here.

```text
[ INSERT WEBSITE SCREENSHOT HERE ]
```

Example after uploading an image named `website-screenshot.png` to your repository:

```md
![Website Screenshot](website-screenshot.png)
```

---

## Database Screenshot

> Add a screenshot from phpMyAdmin showing the `persons` table here.

```text
[ INSERT DATABASE SCREENSHOT HERE ]
```

Example after uploading an image named `database-screenshot.png` to your repository:

```md
![Database Screenshot](database-screenshot.png)
```

---

## Setup Instructions

1. Create a MySQL database through InfinityFree.
2. Create the `persons` table using the SQL command above.
3. Update `db.php` with your InfinityFree MySQL credentials:

```php
<?php
$host = "YOUR_MYSQL_HOST";
$user = "YOUR_MYSQL_USERNAME";
$password = "YOUR_MYSQL_PASSWORD";
$dbname = "YOUR_DATABASE_NAME";

$conn = mysqli_connect($host, $user, $password, $dbname);

if (!$conn) {
    die("Database connection failed: " . mysqli_connect_error());
}
?>
```

4. Upload `index.php` and `db.php` to the `htdocs` folder in InfinityFree.
5. Open the live website link in a browser.

---

## Author

**Name:** Jana Alshomrani  
**Project:** Person Status Manager  
**Hosting:** InfinityFree
