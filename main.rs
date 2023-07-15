use std::io::{self, Write};
use std::fs::{self, File};
use std::io::prelude::*;

const MAX_ENTRIES: usize = 100;

struct Entry {
    date: String,
    title: String,
    content: String,
}

fn add_entry() {
    let mut entry = Entry {
        date: String::new(),
        title: String::new(),
        content: String::new(),
    };

    print!("Enter the date (DD/MM/YYYY): ");
    io::stdout().flush().unwrap();
    io::stdin().read_line(&mut entry.date).unwrap();

    print!("Enter the title: ");
    io::stdout().flush().unwrap();
    io::stdin().read_line(&mut entry.title).unwrap();

    print!("Enter the content: ");
    io::stdout().flush().unwrap();
    io::stdin().read_line(&mut entry.content).unwrap();

    let mut file = fs::OpenOptions::new()
        .create(true)
        .append(true)
        .open("diary.txt")
        .unwrap();

    writeln!(file, "{}\n{}\n{}", entry.date, entry.title, entry.content).unwrap();

    println!("Entry added successfully.");
}

fn view_entry() {
    let mut date = String::new();
    print!("Enter the date (DD/MM/YYYY): ");
    io::stdout().flush().unwrap();
    io::stdin().read_line(&mut date).unwrap();

    let file = File::open("diary.txt").unwrap();
    let reader = io::BufReader::new(file);

    let mut found = false;

    for line in reader.lines() {
        let line = line.unwrap();
        if line == date {
            let title = reader.lines().next().unwrap().unwrap();
            let content = reader.lines().next().unwrap().unwrap();

            println!("Date: {}", date);
            println!("Title: {}", title);
            println!("Content: {}", content);

            found = true;
            break;
        }
    }

    if !found {
        println!("Entry not found.");
    }
}

fn main() {
    let mut choice = String::new();

    loop {
        println!("Diary Management System");
        println!("1. Add entry");
        println!("2. View entry");
        println!("3. Exit");
        print!("Enter your choice: ");
        io::stdout().flush().unwrap();
        io::stdin().read_line(&mut choice).unwrap();

        match choice.trim().parse::<u32>() {
            Ok(1) => add_entry(),
            Ok(2) => view_entry(),
            Ok(3) => {
                println!("Exiting...");
                break;
            }
            _ => println!("Error: Invalid choice."),
        }

        println!();
        choice.clear();
    }
}
