// Utilities for interacting with the MenuBar

import { open } from "@tauri-apps/plugin-dialog";
import { loadFolder } from "../../utils/fs";

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
  console.log("New clicked")
}

export async function handleOpen() {
  const folder = await open({
    multiple: false,
    directory: true
  });
  if (folder) {
    loadFolder(folder);
  }
  console.log("Open clicked", folder);
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