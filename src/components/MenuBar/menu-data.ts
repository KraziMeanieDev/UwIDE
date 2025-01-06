import { handleAbout, handleCopy, handleCut, handleExit, handleNew, handleOpen, handlePaste, handleRedo, handleSave, handleUndo } from "./menu-utils";

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