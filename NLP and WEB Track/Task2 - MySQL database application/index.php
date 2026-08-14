<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

require 'db.php';

$message = "";

/* Add a new person */
if (isset($_POST['submit'])) {
    $name = trim($_POST['name']);
    $age = (int) $_POST['age'];

    if ($name !== "" && $age > 0) {
        $sql = "INSERT INTO persons (name, age, status) VALUES (?, ?, 0)";
        $stmt = mysqli_prepare($conn, $sql);

        mysqli_stmt_bind_param($stmt, "si", $name, $age);

        if (mysqli_stmt_execute($stmt)) {
            $message = "Person added successfully.";
        } else {
            $message = "Could not add the person.";
        }

        mysqli_stmt_close($stmt);
    } else {
        $message = "Enter a valid name and age.";
    }
}

/* Toggle status using AJAX */
if (isset($_POST['toggle_id'])) {
    $id = (int) $_POST['toggle_id'];

    $sql = "UPDATE persons
            SET status = CASE WHEN status = 0 THEN 1 ELSE 0 END
            WHERE id = ?";

    $stmt = mysqli_prepare($conn, $sql);
    mysqli_stmt_bind_param($stmt, "i", $id);
    mysqli_stmt_execute($stmt);
    mysqli_stmt_close($stmt);

    $result = mysqli_query($conn, "SELECT status FROM persons WHERE id = $id");
    $row = mysqli_fetch_assoc($result);

    header("Content-Type: application/json");
    echo json_encode([
        "success" => true,
        "id" => $id,
        "status" => $row["status"]
    ]);
    exit;
}

/* Get all records */
$result = mysqli_query($conn, "SELECT * FROM persons ORDER BY id ASC");
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Person Status Manager</title>

    <style>
        * {
            box-sizing: border-box;
        }

        body {
            margin: 0;
            min-height: 100vh;
            font-family: Arial, sans-serif;
            background: linear-gradient(135deg, #e0f2fe, #f5f3ff);
            color: #172554;
            padding: 45px 18px;
        }

        .container {
            max-width: 930px;
            margin: auto;
            padding: 32px;
            background: #ffffff;
            border-radius: 18px;
            box-shadow: 0 12px 30px rgba(30, 64, 175, 0.15);
        }

        h1 {
            color: #1d4ed8;
            margin-top: 0;
            margin-bottom: 6px;
        }

        .subtitle {
            margin-top: 0;
            color: #64748b;
        }

        .form-card {
            margin: 26px 0;
            padding: 22px;
            background: #eff6ff;
            border: 1px solid #bfdbfe;
            border-radius: 12px;
        }

        form {
            display: flex;
            align-items: end;
            flex-wrap: wrap;
            gap: 15px;
        }

        .field {
            display: flex;
            flex-direction: column;
            gap: 7px;
        }

        label {
            font-weight: bold;
            color: #1e3a8a;
        }

        input {
            width: 230px;
            padding: 11px;
            border: 1px solid #93c5fd;
            border-radius: 8px;
            font-size: 16px;
            outline: none;
        }

        input:focus {
            border-color: #2563eb;
            box-shadow: 0 0 0 3px rgba(37, 99, 235, 0.15);
        }

        button {
            border: none;
            border-radius: 8px;
            padding: 11px 18px;
            font-size: 15px;
            font-weight: bold;
            cursor: pointer;
            transition: 0.2s;
        }

        .submit-btn {
            background: #2563eb;
            color: white;
        }

        .submit-btn:hover {
            background: #1d4ed8;
        }

        .message {
            padding: 12px 15px;
            margin-bottom: 22px;
            border-radius: 8px;
            background: #dcfce7;
            color: #166534;
            font-weight: bold;
        }

        .table-wrapper {
            overflow-x: auto;
        }

        table {
            width: 100%;
            border-collapse: collapse;
            overflow: hidden;
            border-radius: 10px;
        }

        th {
            background: #1d4ed8;
            color: white;
            padding: 14px;
            text-align: left;
        }

        td {
            padding: 13px 14px;
            border-bottom: 1px solid #dbeafe;
        }

        tr:nth-child(even) {
            background: #f8fafc;
        }

        tr:hover {
            background: #eff6ff;
        }

        .status {
            display: inline-block;
            min-width: 78px;
            padding: 6px 10px;
            border-radius: 999px;
            color: white;
            font-weight: bold;
            text-align: center;
        }

        .status-0 {
            background: #ef4444;
        }

        .status-1 {
            background: #16a34a;
        }

        .toggle-btn {
            background: #7c3aed;
            color: white;
        }

        .toggle-btn:hover {
            background: #6d28d9;
        }

        .empty {
            text-align: center;
            color: #64748b;
            padding: 25px;
        }

        @media (max-width: 600px) {
            .container {
                padding: 20px;
            }

            input {
                width: 100%;
            }

            .field {
                width: 100%;
            }

            .submit-btn {
                width: 100%;
            }
        }
    </style>
</head>

<body>

<div class="container">
    <h1>Person Status Manager</h1>
    <p class="subtitle">Add people and toggle their active status.</p>

    <div class="form-card">
        <form method="POST">
            <div class="field">
                <label for="name">Name</label>
                <input id="name" type="text" name="name" placeholder="Enter name" required>
            </div>

            <div class="field">
                <label for="age">Age</label>
                <input id="age" type="number" name="age" min="1" placeholder="Enter age" required>
            </div>

            <button class="submit-btn" type="submit" name="submit">Add Person</button>
        </form>
    </div>

    <?php if ($message !== "") { ?>
        <div class="message"><?php echo $message; ?></div>
    <?php } ?>

    <div class="table-wrapper">
        <table>
            <tr>
                <th>ID</th>
                <th>Name</th>
                <th>Age</th>
                <th>Status</th>
                <th>Action</th>
            </tr>

            <?php if (mysqli_num_rows($result) > 0) { ?>
                <?php while ($row = mysqli_fetch_assoc($result)) { ?>
                    <tr>
                        <td><?php echo $row['id']; ?></td>
                        <td><?php echo htmlspecialchars($row['name']); ?></td>
                        <td><?php echo $row['age']; ?></td>
                        <td>
                            <span
                                id="status-<?php echo $row['id']; ?>"
                                class="status status-<?php echo $row['status']; ?>">
                                <?php echo $row['status']; ?>
                            </span>
                        </td>
                        <td>
                            <button
                                class="toggle-btn"
                                onclick="toggleStatus(<?php echo $row['id']; ?>)">
                                Toggle
                            </button>
                        </td>
                    </tr>
                <?php } ?>
            <?php } else { ?>
                <tr>
                    <td class="empty" colspan="5">No persons added yet.</td>
                </tr>
            <?php } ?>
        </table>
    </div>
</div>

<script>
function toggleStatus(id) {
    const formData = new FormData();
    formData.append("toggle_id", id);

    fetch("index.php", {
        method: "POST",
        body: formData
    })
    .then(response => response.json())
    .then(data => {
        if (data.success) {
            const statusElement = document.getElementById("status-" + id);

            statusElement.textContent = data.status;
            statusElement.className = "status status-" + data.status;
        }
    })
    .catch(error => {
        alert("Could not toggle the status. Try again.");
        console.error(error);
    });
}
</script>

</body>
</html>