#include <iostream>
#include <cmath>
#include <vector>
#include <string>

// --- Mandatory External Library Includes ---
// 1. GLFW for windowing and input (Replace with your windowing library if different)
#include <GLFW/glfw3.h>

// 2. Dear ImGui Core and Backends
#include "imgui.h"
#include "imgui_internal.h" // For PathArcTo, PathLineTo, etc.
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

// --- Global Constants and Data Structures ---

// Define the dimensions of the track for consistent drawing
constexpr float TRACK_WIDTH = 400.0f;  // Total width of the track view
constexpr float TRACK_HEIGHT = 200.0f; // Total height of the track view
constexpr float LANE_WIDTH = 25.0f;    // Width of the track border/lane
constexpr float CORNER_RADIUS = 75.0f; // Radius of the curved ends

// ImGui Colors (0xAARRGGBB format)
const ImU32 COLOR_BLUE_OUTER = IM_COL32(0, 0, 255, 255);       // Opaque Blue
const ImU32 COLOR_YELLOW_ZONE = IM_COL32(255, 255, 0, 128);    // Semi-transparent Yellow
const ImU32 COLOR_TRACK_WHITE = IM_COL32(255, 255, 255, 255);  // Opaque White
const ImU32 COLOR_GREEN_PLAYER = IM_COL32(0, 255, 0, 255);
const ImU32 COLOR_ORANGE_PLAYER = IM_COL32(255, 165, 0, 255);
const ImU32 COLOR_PURPLE_PLAYER = IM_COL32(128, 0, 128, 255);
const ImU32 COLOR_BLACK_INNER = IM_COL32(0, 0, 0, 255);

// Structure to define a player (jammer, pivot, blocker, etc.)
struct Player
{
    ImVec2 position; // Relative position on the track (used for visualization)
    ImU32 color;
    int number;
};

// Dummy data for player positions (will be replaced by your AI state)
std::vector<Player> g_players = {
    {{50, 125}, COLOR_GREEN_PLAYER, 1},
    {{50, 75}, COLOR_GREEN_PLAYER, 2},
    {{200, 150}, COLOR_ORANGE_PLAYER, 3},
    {{250, 50}, COLOR_PURPLE_PLAYER, 1},
    {{350, 150}, COLOR_GREEN_PLAYER, 3},
    {{350, 50}, COLOR_ORANGE_PLAYER, 1},
};


// --- Core Drawing Logic (Retained from previous step) ---

/**
 * Renders the 2D birds-eye view of the roller derby track and players.
 */
void DrawRollerDerbyTrack(ImDrawList* draw_list, ImVec2 center)
{
    // Define the boundaries of the track
    const float half_width = TRACK_WIDTH / 2.0f;
    const float half_height = TRACK_HEIGHT / 2.0f;
    const float straight_len = TRACK_WIDTH - 2.0f * CORNER_RADIUS;

    // Calculate main track corner coordinates
    const ImVec2 P_TL = { center.x - straight_len / 2.0f, center.y - half_height };
    const ImVec2 P_TR = { center.x + straight_len / 2.0f, center.y - half_height };
    const ImVec2 P_BL = { center.x - straight_len / 2.0f, center.y + half_height };
    // const ImVec2 P_BR = { center.x + straight_len / 2.0f, center.y + half_height }; // Not needed for drawing loop

    // Calculate the center points for the two semicircles
    const ImVec2 left_center = { P_TL.x, center.y };
    const ImVec2 right_center = { P_TR.x, center.y };

    // --- 1. Draw the main track area (Filled White/Light Gray) ---
    draw_list->PathClear();
    draw_list->PathLineTo(P_TL);
    draw_list->PathLineTo(P_TR);
    // Right semicircle (90 deg to 270 deg)
    draw_list->PathArcTo(right_center, half_height, IM_PI * 1.5f, IM_PI * 0.5f, 20);
    // Bottom straight
    draw_list->PathLineTo({P_TR.x, P_BL.y}); // Manually specify bottom right corner
    // Left semicircle (270 deg to 90 deg)
    draw_list->PathArcTo(left_center, half_height, IM_PI * 0.5f, IM_PI * 1.5f, 20);
    draw_list->PathFillConvex(COLOR_TRACK_WHITE);


    // --- 2. Draw the inner boundary (Center oval stroke) ---
    const float inner_radius_y = half_height - LANE_WIDTH;
    const float inner_radius_x_start = P_TL.x;
    const float inner_radius_x_end = P_TR.x;

    draw_list->PathClear();
    draw_list->PathLineTo({inner_radius_x_start, center.y - inner_radius_y});
    draw_list->PathLineTo({inner_radius_x_end, center.y - inner_radius_y});
    draw_list->PathArcTo(right_center, inner_radius_y, IM_PI * 1.5f, IM_PI * 0.5f, 20);
    draw_list->PathLineTo({inner_radius_x_end, center.y + inner_radius_y});
    draw_list->PathLineTo({inner_radius_x_start, center.y + inner_radius_y});
    draw_list->PathArcTo(left_center, inner_radius_y, IM_PI * 0.5f, IM_PI * 1.5f, 20);
    draw_list->PathStroke(COLOR_BLACK_INNER, ImDrawFlags_Closed, 2.0f);


    // --- 3. Draw the Outer Track Boundary (Blue Stroke) ---
    draw_list->PathClear();
    draw_list->PathLineTo(P_TL);
    draw_list->PathLineTo(P_TR);
    draw_list->PathArcTo(right_center, half_height, IM_PI * 1.5f, IM_PI * 0.5f, 20);
    draw_list->PathLineTo(P_BL);
    draw_list->PathArcTo(left_center, half_height, IM_PI * 0.5f, IM_PI * 1.5f, 20);
    draw_list->PathStroke(COLOR_BLUE_OUTER, ImDrawFlags_Closed, LANE_WIDTH / 2.0f);

    // --- 4. Draw the Yellow Zone (Pivot Line area) ---
    const float yellow_zone_width = straight_len / 3.0f;
    const ImVec2 YZ_P1 = { P_TL.x + yellow_zone_width, P_TL.y };
    const ImVec2 YZ_P2 = { P_TL.x, P_BL.y };
    draw_list->AddRectFilled(YZ_P1, YZ_P2, COLOR_YELLOW_ZONE);
    
    // Draw the main line of the yellow zone (the Pivot Line)
    draw_list->AddLine({YZ_P1.x, YZ_P1.y}, {YZ_P1.x, YZ_P2.y}, COLOR_BLACK_INNER, 2.0f);


    // --- 5. Draw the Players (Circles) ---
    const float player_radius = 10.0f;
    const float half_track_width = TRACK_WIDTH / 2.0f;
    const float half_track_height = TRACK_HEIGHT / 2.0f;


    for (const auto& player : g_players)
    {
        // Convert player's relative position (0 to TRACK_WIDTH/HEIGHT)
        // to screen coordinates relative to the track's center.
        ImVec2 screen_pos = { 
            center.x - half_track_width + player.position.x, 
            center.y - half_track_height + player.position.y 
        };

        // Draw the main body of the player (a filled circle)
        draw_list->AddCircleFilled(screen_pos, player_radius, player.color);

        // Draw the outline/border
        draw_list->AddCircle(screen_pos, player_radius, COLOR_BLACK_INNER, 12, 2.0f);

        // Draw the player number (text)
        std::string num_str = std::to_string(player.number);
        // Center the text
        draw_list->AddText(
            { screen_pos.x - draw_list->_Data->FontSize * 0.3f, screen_pos.y - draw_list->_Data->FontSize * 0.5f },
            COLOR_BLACK_INNER,
            num_str.c_str()
        );
    }
}


/**
 * Renders all ImGui elements, including the track visualization and control panel.
 */
void RenderGameGUI()
{
    // --- 1. ImGui Frame Setup ---
    // All ImGui functions must be called between ImGui::Begin() and ImGui::End()

    ImGui::Begin("AI Roller Derby Simulation View");

    // Set a consistent initial window size (Track dimensions + padding)
    ImGui::SetWindowSize({ TRACK_WIDTH + 80.0f, TRACK_HEIGHT + 150.0f }, ImGuiCond_Once);

    // Get the window's draw list and the current cursor position on screen
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 cursor_pos = ImGui::GetCursorScreenPos();

    // Calculate the center point for the track drawing, leaving margin
    ImVec2 track_center = { cursor_pos.x + 40.0f + TRACK_WIDTH / 2.0f, cursor_pos.y + 40.0f + TRACK_HEIGHT / 2.0f };

    // --- 2. Draw the Track ---
    DrawRollerDerbyTrack(draw_list, track_center);

    // Reserve space in the ImGui layout for the track visualization,
    // so other widgets draw below it.
    ImGui::Dummy({ TRACK_WIDTH + 80.0f, TRACK_HEIGHT + 80.0f });

    // --- 3. Control Panel (Where you manage your AI training) ---
    ImGui::Separator();
    ImGui::Text("Simulation Controls:");
    if (ImGui::Button("Start Training"))
    {
        // In a real app, this button would launch your AI training thread
        std::cout << "Starting AI Training..." << std::endl;
    }
    ImGui::SameLine();
    if (ImGui::Button("Pause"))
    {
        // Logic to signal your training thread to pause
        std::cout << "Pausing simulation..." << std::endl;
    }

    ImGui::End();
}


// --- Main Application Boilerplate ---

int main(int, char**)
{
    // --- 1. GLFW Initialization (Window and Context) ---
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.3 + GLSL 330
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "AI Roller Derby ImGui Demo", nullptr, nullptr);
    if (window == nullptr)
        return 1;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // NOTE: If you are using GLAD or GLEW, you must initialize them here.
    // E.g., if using GLEW: if (glewInit() != GLEW_OK) { /* handle error */ }

    // --- 2. Dear ImGui Context Setup ---
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    // --- 3. Main Application Loop ---
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- RENDER YOUR GUI CONTENT HERE ---
        RenderGameGUI();

        // --- RENDERING ---
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // --- 4. Cleanup ---
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

