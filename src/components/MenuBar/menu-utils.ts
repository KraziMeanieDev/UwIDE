import { invoke } from "@tauri-apps/api/core";
import { join } from "@tauri-apps/api/path";
import { open } from "@tauri-apps/plugin-dialog";
import { readDir } from "@tauri-apps/plugin-fs";

export async function handleNew() {
  await invoke("create_new_file");
}

export async function handleOpen() {
  const folder = await open({
    multiple: false,
    directory: true,
  });

  if (folder) {
    // Check if folder is not null
    try {
      const entries = await readDir(folder);

      const children = await Promise.all(
        entries.map(async (entry) => {
          const fullPath = await join(folder, entry.name);
          return {
            ...entry,
            path: fullPath,
          };
        }),
      );
      console.log("Open clicked", children);
    } catch (error) {
      console.error("Error reading directory:", error);
      // Handle the error appropriately, e.g., display an error message to the user
    }
  } else {
    console.log("User cancelled the folder selection.");
  }
}

export function handleSave() {
  console.log("Save clicked");
}

export function handleExit() {
  console.log("Exit clicked");
}

// Functions for Edit menu
export function handleUndo() {
  console.log("Undo clicked");
}

export function handleRedo() {
  console.log("Redo clicked");
}

export function handleCut() {
  console.log("Cut clicked");
}

export function handleCopy() {
  console.log("Copy clicked");
}

export function handlePaste() {
  console.log("Paste clicked");
}

// Functions for Help menu
export function handleAbout() {
  console.log("About clicked");
}