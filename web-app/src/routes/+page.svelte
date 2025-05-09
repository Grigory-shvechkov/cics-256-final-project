<script lang="ts">
    import { Button } from "$lib/components/ui/button";
    import ChevronUp from "@lucide/svelte/icons/chevron-up";
    import ChevronDown from "@lucide/svelte/icons/chevron-down";
    import RotateCCW from "@lucide/svelte/icons/rotate-ccw";
    import RotateCW from "@lucide/svelte/icons/rotate-cw";
    import Ban from "@lucide/svelte/icons/ban";

    async function handleForwardClick() {
        await fetch("http://192.168.4.1/move?direction=forward", {
            method: "GET",
            headers: {
                "Content-Type": "application/json",
            },
        });
    };

    async function handleBackwardClick() {
        await fetch("http://192.168.4.1/move?direction=backward", {
            method: "GET",
            headers: {
                "Content-Type": "application/json",
            },
        });
    };

    async function handleLeftClick() {
        await fetch("http://192.168.4.1/move?direction=left", {
            method: "GET",
            headers: {
                "Content-Type": "application/json",
            },
        });
    };

    async function handleRightClick() {
        await fetch("http://192.168.4.1/move?direction=right", {
            method: "GET",
            headers: {
                "Content-Type": "application/json",
            },
        });
    };

    async function handleStopClick() {
        await fetch("http://192.168.4.1/move?direction=stop", {
            method: "GET",
            headers: {
                "Content-Type": "application/json",
            },
        });
    };
</script>

<div class="min-h-screen flex items-center justify-center p-8">
    <div class="flex flex-col items-center justify-center gap-16 bg-zinc-900 border-4 rounded-xl p-8">
        <h1 class="text-center text-3xl font-bold tracking-tight">QUADRUPED ROBOT CONTROL</h1>
        <div class="grid grid-cols-3 grid-rows-3 items-center justify-items-center gap-4">
            <div></div>
            <Button onclick={handleForwardClick} class="size-20 border-4 rounded-xl" variant="outline">
                <ChevronUp />
            </Button>
            <div></div>
            <Button onclick={handleLeftClick} class="size-20 border-4 rounded-xl" variant="outline">
                <RotateCCW />
            </Button>
            <Button onclick={handleStopClick} class="size-20 border-4 rounded-xl" variant="destructive">
                <Ban />
            </Button>
            <Button onclick={handleRightClick} class="size-20 border-4 rounded-xl" variant="outline">
                <RotateCW />
            </Button>
            <div></div>
            <Button onclick={handleBackwardClick} class="size-20 border-4 rounded-xl" variant="outline">
                <ChevronDown />
            </Button>
            <div></div>
        </div>
    </div>
</div>
