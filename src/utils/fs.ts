// Utility functions for interacting with the file system

import { join } from "@tauri-apps/api/path";
import { readDir, type DirEntry } from "@tauri-apps/plugin-fs";
import { writable, type Writable } from "svelte/store";

export interface DirEntriesWithPath extends DirEntry {
    path: string;
}

export const currentFolderItems: Writable<DirEntriesWithPath[]> = writable([]);

export async function loadFolder(folderPath: string) {
    if (folderPath) {
        // Check if folder is not null
        try {
            const results = await readDir(folderPath);

            const folderEntries = await Promise.all(
                results.map(async (entry) => {
                    const fullPath = await join(folderPath, entry.name);
                    return {
                        ...entry,
                        path: fullPath,
                    };
                }),
            );
            currentFolderItems.set(folderEntries.sort((a: DirEntriesWithPath, b: DirEntriesWithPath) => {
                // Guarantee that items are sorted folders first in alphabetical order
                if (a.isDirectory && !b.isDirectory) {
                    return -1;
                } else if (!a.isDirectory && b.isDirectory) {
                    return 1
                } else return a.name.localeCompare(b.name);
            }));
            console.log("Folder Items List: ", folderEntries);
        } catch (error) {
            console.error("Error reading directory:", error);
            // Handle the error appropriately, e.g., display an error message to the user
        }
    } else {
        return [];
        console.log("User cancelled the folder selection.");
    }
}