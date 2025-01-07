// Utilities for interacting with the MenuBar

import { open } from "@tauri-apps/plugin-dialog";
import { loadFile, loadFolder } from "../../utils/fs";

export let menuItems = [
  {
    label: "File",
    submenu: [
      { label: "New", action: () => handleNew() },
      { label: "Open", action: () => handleOpen() },
      { label: "Save", action: () => handleSave() },
      { label: "Exit", action: () => handleExit() },
    ],
  },
  {
    label: "Edit",
    submenu: [
      { label: "Undo", action: () => handleUndo() },
      { label: "Redo", action: () => handleRedo() },
      { label: "Cut", action: () => handleCut() },
      { label: "Copy", action: () => handleCopy() },
      { label: "Paste", action: () => handlePaste() },
    ],
  },
  {
    label: "Help",
    submenu: [{ label: "About", action: () => handleAbout() }],
  },
];

export async function handleNew() {
  const filePath = await open({
    filters: [{ name: "Cpp Files", extensions: ["cpp"] }],
  });
  if (filePath) {
    await loadFile(filePath);
  }
  console.log(filePath);
}

export async function handleOpen() {
  const folderPath = await open({
    multiple: false,
    directory: true
  });
  if (folderPath) {
    loadFolder(folderPath);
  }
  console.log("Open clicked", folderPath);
}

export async function handleSave() {
  console.log("Save clicked");
}

export async function handleExit() {
  console.log("Exit clicked");
}


export async function handleUndo() {
  console.log("Undo clicked");
}

export async function handleRedo() {
  console.log("Redo clicked");
}

export async function handleCut() {
  console.log("Cut clicked");
}

export async function handleCopy() {
  console.log("Copy clicked");
}

export async function handlePaste() {
  console.log("Paste clicked");
}

// Functions for Help menu
export async function handleAbout() {
  console.log("About clicked");
}