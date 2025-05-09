<script lang="ts">
    import { Button } from "$lib/components/ui/button";
    import ChevronUp from "@lucide/svelte/icons/chevron-up";

    async function handleForwardClick() {
        console.log("here");
        const response = await fetch("http://192.168.4.1/move/forward", {
            method: "GET",
            headers: {
                "Content-Type": "application/json",
            },
        });
    };

    async function handleForwardStopClick() {
        console.log("here");
        const response = await fetch("http://192.168.4.1/move/forward?stop=true", {
            method: "GET",
            headers: {
                "Content-Type": "application/json",
            },
        });
    };

    async function handleBackwardClick() {
        console.log("here");
        const response = await fetch("http://192.168.4.1/move/backward", {
            method: "GET",
            headers: {
                "Content-Type": "application/json",
            },
        });
    };

    async function handleBackwardStopClick() {
        console.log("here");
        const response = await fetch("http://192.168.4.1/move/backward?stop=true", {
            method: "GET",
            headers: {
                "Content-Type": "application/json",
            },
        });
    };

    async function handleLeftClick() {
        console.log("here");
        const response = await fetch("http://192.168.4.1/move/rotate-left", {
            method: "GET",
            headers: {
                "Content-Type": "application/json",
            },
        });
    };

    async function handleLeftStopClick() {
        console.log("here");
        const response = await fetch("http://192.168.4.1/move/rotate-left?stop=true", {
            method: "GET",
            headers: {
                "Content-Type": "application/json",
            },
        });
    };

    async function handleRightClick() {
        console.log("here");
        const response = await fetch("http://192.168.4.1/move/rotate-right", {
            method: "GET",
            headers: {
                "Content-Type": "application/json",
            },
        });
    };

    async function handleRightStopClick() {
        console.log("here");
        const response = await fetch("http://192.168.4.1/move/rotate-right?stop=true", {
            method: "GET",
            headers: {
                "Content-Type": "application/json",
            },
        });
    };
</script>

<div class="flex flex-col items-center gap-8 p-8">
    <h1 class="text-center text-4xl font-semibold">Robot Spider Control</h1>
    <div class="flex flex-col">
        <Button onclick={handleForwardClick}>
            <ChevronUp />
        </Button>
        <Button onclick={handleForwardStopClick}>
            STOP FORWARD
        </Button>
        <Button onclick={handleBackwardClick}>
            <ChevronUp class="rotate-180" />
        </Button>
        <Button onclick={handleBackwardStopClick}>
            STOP BACKWARD
        </Button>
        <div class="flex gap-4">
            <Button onclick={handleLeftClick}>
                LEFT
            </Button>
            <Button onclick={handleRightClick}>
                RIGHT
            </Button>
        </div>
        <div class="flex gap-4">
            <Button onclick={handleLeftStopClick}>
                STOP LEFT
            </Button>
            <Button onclick={handleRightStopClick}>
                STOP RIGHT
            </Button>
        </div>
    </div>
</div>
