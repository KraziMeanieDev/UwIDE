import type { EditorView } from "codemirror";
import { get, writable, type Writable } from "svelte/store";
import { basename } from "@tauri-apps/api/path";
import { createNewEditorView, createInitialEditorView } from "./editor-utils";
import { remove } from "@tauri-apps/plugin-fs";

export interface Tab {
    id: string;
    title: string;
    path: string;
    editorView: EditorView | null;
}

const initialTab: Tab = {
    id: crypto.randomUUID(),
    title: "Untitled-1.cpp",
    editorView: createInitialEditorView(),
    path: "",
};

export const editorTabs: Writable<Tab[]> = writable([initialTab]);
export const activeTabId: Writable<string> = writable(initialTab.id);

export async function addTab(path: string) {
    const existingTabs = get(editorTabs);
    const tabAlreadyOpened = existingTabs.find(tab => tab.path === path);

    if (tabAlreadyOpened) {
        activeTabId.set(tabAlreadyOpened.id);
        return;
    }

    const newEditorView = await createNewEditorView(path);
    if (newEditorView) {
        const newTab: Tab = {
            id: crypto.randomUUID(),
            title: await basename(path),
            path: path,
            editorView: newEditorView,
        };
        editorTabs.update((tabs) => {
            activeTabId.set(newTab.id);
            return [...tabs, newTab];
        });
    } else {
        console.error("Failed to create editor for:", path);
    }
}

export async function removeTab(id: string, currentActiveTab: string) {
    editorTabs.update((tabs) => {
        const removedTabIndex = tabs.findIndex((tab) => tab.id === id);
        const removedTab = tabs.find((tab) => tab.id === id);
        const updatedTabs = tabs.filter((tab) => tab.id !== id);

        if (removedTab?.editorView) {
            removedTab.editorView.destroy();
            console.log(`${removedTab.title} was destroyed`)
        }

        if (updatedTabs.length > 0) { // Check if there's other tabs after a tab has been removed
            if (id === currentActiveTab) { // Check if the tab being removed is the currently active tab
                let newActiveTabIndex: number;
                if (removedTabIndex >= updatedTabs.length) { // Check if the removed tab was the last on in the list
                    newActiveTabIndex = updatedTabs.length - 1;
                    activeTabId.set(updatedTabs[newActiveTabIndex].id) // If it was the last, set the new active tab to the preview tab in the list.
                }
            }
        } else {
            activeTabId.set("");
        }

        return updatedTabs;
    })
}