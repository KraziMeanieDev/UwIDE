// Prevents additional console window on Windows in release, DO NOT REMOVE!!
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

#[tauri::command]
fn create_new_file() {
    println!("Creating a new file...");
}

fn main() {
    tauri::Builder::default()
    .invoke_handler(tauri::generate_handler![create_new_file])
    .run(tauri::generate_context!())
    .expect("error while running application");
    uwide_lib::run();
}
