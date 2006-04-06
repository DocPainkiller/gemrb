/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/FXOpcodes/FXOpc.cpp,v 1.12 2006/04/06 21:14:39 avenger_teambg Exp $
 *
 */

#include "../../includes/win32def.h"
#include "../../includes/strrefs.h"
#include "../Core/Actor.h"
#include "../Core/EffectQueue.h"
#include "../Core/Interface.h"
#include "../Core/ResourceMgr.h"
#include "../Core/SoundMgr.h"
#include "../Core/Game.h"
#include "../Core/damages.h"
#include "../Core/TileMap.h"  //needs for knock!
#include "FXOpc.h"


int fx_ac_vs_damage_type_modifier (Actor* Owner, Actor* target, Effect* fx);//00
int fx_attacks_per_round_modifier (Actor* Owner, Actor* target, Effect* fx);//01
int fx_cure_sleep_state (Actor* Owner, Actor* target, Effect* fx);//02
int fx_set_berserk_state (Actor* Owner, Actor* target, Effect* fx);//03
int fx_cure_berserk_state (Actor* Owner, Actor* target, Effect* fx);//04
int fx_set_charmed_state (Actor* Owner, Actor* target, Effect* fx);//05
int fx_charisma_modifier (Actor* Owner, Actor* target, Effect* fx);//06
int fx_set_color_gradient (Actor* Owner, Actor* target, Effect* fx);//07
int fx_set_color_rgb (Actor* Owner, Actor* target, Effect* fx);//08
int fx_set_color_pulse_rgb (Actor* Owner, Actor* target, Effect* fx);//09
int fx_constitution_modifier (Actor* Owner, Actor* target, Effect* fx);//0a
int fx_cure_poisoned_state (Actor* Owner, Actor* target, Effect* fx);//0b
int fx_damage (Actor* Owner, Actor* target, Effect* fx);//0c
int fx_death (Actor* Owner, Actor* target, Effect* fx);//0d
int fx_cure_frozen_state (Actor* Owner, Actor* target, Effect* fx);//0e
int fx_dexterity_modifier (Actor* Owner, Actor* target, Effect* fx);//0f
int fx_set_hasted_state (Actor* Owner, Actor* target, Effect* fx);//10
int fx_current_hp_modifier (Actor* Owner, Actor* target, Effect* fx);//11
int fx_maximum_hp_modifier (Actor* Owner, Actor* target, Effect* fx);//12
int fx_intelligence_modifier (Actor* Owner, Actor* target, Effect* fx);//13
int fx_set_invisible_state (Actor* Owner, Actor* target, Effect* fx);//14
int fx_lore_modifier (Actor* Owner, Actor* target, Effect* fx);//15
int fx_luck_modifier (Actor* Owner, Actor* target, Effect* fx);//16
int fx_morale_modifier (Actor* Owner, Actor* target, Effect* fx);//17
int fx_set_panic_state (Actor* Owner, Actor* target, Effect* fx);//18
int fx_set_poisoned_state (Actor* Owner, Actor* target, Effect* fx);//19
int fx_remove_curse (Actor* Owner, Actor* target, Effect* fx);//1a
int fx_acid_resistance_modifier (Actor* Owner, Actor* target, Effect* fx);//1b
int fx_cold_resistance_modifier (Actor* Owner, Actor* target, Effect* fx);//1c
int fx_electricity_resistance_modifier (Actor* Owner, Actor* target, Effect* fx);//1d
int fx_fire_resistance_modifier (Actor* Owner, Actor* target, Effect* fx);//1e
int fx_magic_damage_resistance_modifier (Actor* Owner, Actor* target, Effect* fx);//1f
int fx_cure_dead_state (Actor* Owner, Actor* target, Effect* fx);//20
int fx_save_vs_death_modifier (Actor* Owner, Actor* target, Effect* fx);//21
int fx_save_vs_wands_modifier (Actor* Owner, Actor* target, Effect* fx);//22
int fx_save_vs_poly_modifier (Actor* Owner, Actor* target, Effect* fx);//23
int fx_save_vs_breath_modifier (Actor* Owner, Actor* target, Effect* fx);//24
int fx_save_vs_spell_modifier (Actor* Owner, Actor* target, Effect* fx);//25
int fx_set_silenced_state (Actor* Owner, Actor* target, Effect* fx);//26
int fx_set_unconscious_state (Actor* Owner, Actor* target, Effect* fx);//27
int fx_set_slowed_state (Actor* Owner, Actor* target, Effect* fx);//28
int fx_sparkle(Actor* Owner, Actor* target, Effect* fx);//29
int fx_bonus_wizard_spells (Actor* Owner, Actor* target, Effect* fx);//2a
int fx_cure_petrified_state (Actor* Owner, Actor* target, Effect* fx);//2b
int fx_strength_modifier (Actor* Owner, Actor* target, Effect* fx);//2c
int fx_set_stun_state (Actor* Owner, Actor* target, Effect* fx);//2d
int fx_cure_stun_state (Actor* Owner, Actor* target, Effect* fx);//2e
int fx_cure_invisible_state (Actor* Owner, Actor* target, Effect* fx);//2f
int fx_cure_silenced_state (Actor* Owner, Actor* target, Effect* fx);//30
int fx_wisdom_modifier (Actor* Owner, Actor* target, Effect* fx);//31
int fx_rgb_pulsate (Actor* Owner, Actor* target, Effect* fx);//32
int fx_rgb_darken (Actor* Owner, Actor* target, Effect* fx);//33
int fx_rgb_glow (Actor* Owner, Actor* target, Effect* fx);//34
int fx_animation_id_modifier (Actor* Owner, Actor* target, Effect* fx);//35
int fx_to_hit_modifier (Actor* Owner, Actor* target, Effect* fx);//36
int fx_kill_creature_type (Actor* Owner, Actor* target, Effect* fx);//37
int fx_alignment_invert (Actor* Owner, Actor* target, Effect* fx);//38
int fx_alignment_change (Actor* Owner, Actor* target, Effect* fx);//39
int fx_dispel_effects (Actor* Owner, Actor* target, Effect* fx);//3a
int fx_stealth_modifier (Actor* Owner, Actor* target, Effect* fx);//3b
int fx_miscast_magic_modifier (Actor* Owner, Actor* target, Effect* fx);//3c
int fx_alchemy_modifier (Actor* Owner, Actor* target, Effect* fx);//3d
int fx_bonus_priest_spells (Actor* Owner, Actor* target, Effect* fx);//3e
int fx_set_infravision_state (Actor* Owner, Actor* target, Effect* fx);//3f
int fx_cure_infravision_state (Actor* Owner, Actor* target, Effect* fx);//40
int fx_set_blur_state (Actor* Owner, Actor* target, Effect* fx);//41
int fx_transparency_modifier (Actor* Owner, Actor* target, Effect* fx);//42
int fx_summon_creature (Actor* Owner, Actor* target, Effect* fx);//43
int fx_unsummon_creature (Actor* Owner, Actor* target, Effect* fx);//44
int fx_set_nondetection_state (Actor* Owner, Actor* target, Effect* fx);//45
int fx_cure_nondetection_state (Actor* Owner, Actor* target, Effect* fx);//46
int fx_sex_modifier (Actor* Owner, Actor* target, Effect* fx);//47
int fx_ids_modifier (Actor* Owner, Actor* target, Effect* fx);//48
int fx_damage_bonus_modifier (Actor* Owner, Actor* target, Effect* fx);//49
int fx_set_blind_state (Actor* Owner, Actor* target, Effect* fx);//4a
int fx_cure_blind_state (Actor* Owner, Actor* target, Effect* fx);//4b
int fx_set_feebleminded_state (Actor* Owner, Actor* target, Effect* fx);//4c
int fx_cure_feebleminded_state (Actor* Owner, Actor* target, Effect* fx);//4d
int fx_set_diseased_state (Actor* Owner, Actor* target, Effect*fx);//4e
int fx_cure_diseased_state (Actor* Owner, Actor* target, Effect* fx);//4f
int fx_set_deaf_state (Actor* Owner, Actor* target, Effect* fx); //50
int fx_cure_deaf_state (Actor* Owner, Actor* target, Effect* fx);//51
int fx_set_ai_script (Actor* Owner, Actor* target, Effect*fx);//52
int fx_protection_from_projectile (Actor* Owner, Actor* target, Effect*fx);//53
int fx_magical_fire_resistance_modifier (Actor* Owner, Actor* target, Effect* fx);//54
int fx_magical_cold_resistance_modifier (Actor* Owner, Actor* target, Effect* fx);//55
int fx_slashing_resistance_modifier (Actor* Owner, Actor* target, Effect* fx);//56
int fx_crushing_resistance_modifier (Actor* Owner, Actor* target, Effect* fx);//57
int fx_piercing_resistance_modifier (Actor* Owner, Actor* target, Effect* fx);//58
int fx_missiles_resistance_modifier (Actor* Owner, Actor* target, Effect* fx);//59
int fx_open_locks_modifier (Actor* Owner, Actor* target, Effect* fx);//5a
int fx_find_traps_modifier (Actor* Owner, Actor* target, Effect* fx);//5b
int fx_pick_pockets_modifier (Actor* Owner, Actor* target, Effect* fx);//5c
int fx_fatigue_modifier (Actor* Owner, Actor* target, Effect* fx);//5d
int fx_intoxication_modifier (Actor* Owner, Actor* target, Effect* fx);//5e
int fx_tracking_modifier (Actor* Owner, Actor* target, Effect* fx);//5f
int fx_level_modifier (Actor* Owner, Actor* target, Effect* fx);//60
int fx_strength_bonus_modifier (Actor* Owner, Actor* target, Effect* fx);//61
int fx_state_regeneration (Actor* Owner, Actor* target, Effect* fx);//62
int fx_spell_duration_modifier (Actor* Owner, Actor* target, Effect* fx);///63
int fx_generic_effect (Actor* Owner, Actor* target, Effect* fx);//64 protection from creature is a generic effect
//65 protection from opcode is a generic effect
//66 protection from spell level is a generic effect
int fx_change_name (Actor* Owner, Actor* target, Effect* fx);//67
int fx_experience_modifier (Actor* Owner, Actor* target, Effect* fx);//68
int fx_gold_modifier (Actor* Owner, Actor* target, Effect* fx);//69
int fx_morale_break_modifier (Actor* Owner, Actor* target, Effect* fx);//6a
int fx_portrait_change (Actor* Owner, Actor* target, Effect* fx);//6b
int fx_reputation_modifier (Actor* Owner, Actor* target, Effect* fx);//6c
int fx_hold_creature_no_icon (Actor* Owner, Actor* target, Effect* fx);//6d
int fx_retreat_from (Actor* Owner, Actor* target, Effect* fx);//6e (unknown)
int fx_create_magic_item (Actor* Owner, Actor* target, Effect* fx);//6f
int fx_remove_item (Actor* Owner, Actor* target, Effect* fx);//70
int fx_equip_item (Actor* Owner, Actor* target, Effect* fx);//71
int fx_dither (Actor* Owner, Actor* target, Effect* fx);//72
int fx_detect_alignment (Actor* Owner, Actor* target, Effect* fx);//73
int fx_cure_improved_invisible_state (Actor* Owner, Actor* target, Effect* fx);//74
int fx_reveal_area (Actor* Owner, Actor* target, Effect* fx);//75
//76
//77
//78
//79
int fx_create_inventory_item (Actor* Owner, Actor* target, Effect* fx);//7a
int fx_remove_inventory_item (Actor* Owner, Actor* target, Effect* fx);//7b
int fx_dimension_door (Actor* Owner, Actor* target, Effect* fx);//7c
int fx_knock (Actor* Owner, Actor* target, Effect* fx);//7d
int fx_movement_modifier (Actor* Owner, Actor* target, Effect* fx);//7e
//7f
int fx_set_confused_state (Actor* Owner, Actor* target, Effect* fx);//80
int fx_set_aid_state (Actor* Owner, Actor* target, Effect* fx);//81
int fx_set_bless_state (Actor* Owner, Actor* target, Effect* fx);//82
//83
//84
//85
int fx_set_petrified_state (Actor* Owner, Actor* target, Effect* fx);//86
//87
//88
//89
//8a
int fx_display_string (Actor* Owner, Actor* target, Effect* fx);//8b
//8c
//8d
int fx_display_portrait_icon (Actor* Owner, Actor* target, Effect* fx);//8e
int fx_create_item_in_slot (Actor* Owner, Actor* target, Effect* fx);//8f
int fx_disable_button (Actor* Owner, Actor* target, Effect* fx);//90
int fx_disable_spellcasting (Actor* Owner, Actor* target, Effect* fx);//91
//92
int fx_learn_spell (Actor* Owner, Actor* target, Effect *fx);//93
//94
//95
//96
//97
int fx_play_movie (Actor* Owner, Actor* target, Effect* fx);//98
int fx_set_sanctuary_state (Actor* Owner, Actor* target, Effect* fx);//99
int fx_set_entangle_state (Actor* Owner, Actor* target, Effect* fx);//9a
int fx_set_minorglobe_state (Actor* Owner, Actor* target, Effect* fx);//9b
int fx_set_shieldglobe_state (Actor* Owner, Actor* target, Effect* fx);//9c
int fx_set_web_state (Actor* Owner, Actor* target, Effect* fx);//9d
int fx_set_grease_state (Actor* Owner, Actor* target, Effect* fx);//9e
//9f
int fx_cure_sanctuary_state (Actor* Owner, Actor* target, Effect* fx);//a0
int fx_cure_panic_state (Actor* Owner, Actor* target, Effect* fx);//a1
int fx_cure_hold_state (Actor* Owner, Actor* target, Effect* fx);//a2 //cures 175
int fx_cure_slow_state (Actor* Owner, Actor* target, Effect* fx);//a3
//a4
int fx_pause_target (Actor* Owner, Actor* target, Effect* fx);//a5
int fx_magic_resistance_modifier (Actor* Owner, Actor* target, Effect* fx);//a6
int fx_missile_to_hit_modifier (Actor* Owner, Actor* target, Effect* fx);//a7
int fx_remove_creature (Actor* Owner, Actor* target, Effect* fx);//a8
int fx_disable_portrait_icon (Actor* Owner, Actor* target, Effect* fx);//a9
//aa
//ab
//ac
//ad
int fx_playsound (Actor* Owner, Actor* target, Effect* fx);//ae
int fx_hold_creature (Actor* Owner, Actor* target, Effect* fx);//af
// this function is exactly the same as 0x7e fx_movement_modifier (in bg2 at least)//b0
//b1
//b2
//b3
//b4
//b5
//b6
//b7
//b8
// this function is exactly the same as 0xaf hold_creature (in bg2 at least) //b9
int fx_destroy_self (Actor* Owner, Actor* target, Effect* fx);//ba
int fx_local_variable (Actor* Owner, Actor* target, Effect* fx);//bb
//bc
//bd
//be
int fx_spell_casting_level_modifier (Actor* Owner, Actor* target, Effect* fx);//bf
//c0
int fx_see_invisible_modifier (Actor* Owner, Actor* target, Effect* fx);//c1
int fx_ignore_dialogpause_modifier (Actor* Owner, Actor* target, Effect* fx);//c2
//c3
//c4
int fx_bounce_projectile (Actor* Owner, Actor* target, Effect* fx);//c5
//c6
//c7
//c8
//c9
//ca
//cb
//cc
//cd
//ce
//cf
int fx_minimum_hp_modifier (Actor* Owner, Actor* target, Effect* fx);//d0
int fx_power_word_kill (Actor* Owner, Actor* target, Effect* fx);//d1
//d2
//d3
//d4
//d5
//d6
int fx_play_visual_effect (Actor* Owner, Actor* target, Effect* fx); //d7
//d8
//d9
int fx_stoneskin_modifier (Actor* Owner, Actor* target, Effect* fx); //da
//db
//dc
//dd
//de
//df
//e0
//e1
//e2
//e3
//e4
//e5
//e6
//e7
//e8
int fx_proficiency (Actor* Owner, Actor* target, Effect* fx);//e9
int fx_create_contingency (Actor* Owner, Actor* /*target*/, Effect* fx);//ea
int fx_wing_buffet (Actor* Owner, Actor* target, Effect* fx);//eb
int fx_puppet_master (Actor* Owner, Actor* target, Effect* fx);//ec
int fx_puppet (Actor* Owner, Actor* target, Effect* fx);//ed
int fx_disintegrate (Actor* Owner, Actor* target, Effect* fx);//ee
int fx_farsee (Actor* Owner, Actor* target, Effect* fx);//ef
int fx_remove_portrait_icon (Actor* Owner, Actor* target, Effect* fx);//f0
//f1
int fx_cure_confused_state (Actor* Owner, Actor* target, Effect* fx);//f2
//f3
//f4
//f5
//f6
//f7
//f8
//f9
//fa
//fb
//fc
//fd
//fe
int fx_create_item_days (Actor* Owner, Actor* target, Effect* fx);//ff
int fx_store_spell_sequencer (Actor* Owner, Actor* target, Effect* fx);//0x100
int fx_create_spell_sequencer (Actor* Owner, Actor* target, Effect* fx);//101
int fx_activate_spell_sequencer (Actor* Owner, Actor* target, Effect* fx);//102
int fx_spelltrap (Actor* Owner, Actor* target, Effect* fx);//103
//104 //crashes so far
int fx_restore_spell_level (Actor* Owner, Actor* target, Effect* fx);//105
int fx_visual_range_modifier (Actor* Owner, Actor* target, Effect* fx);//106
int fx_backstab_modifier (Actor* Owner, Actor* target, Effect* fx);//107
int fx_drop_weapon (Actor* Owner, Actor* target, Effect* fx);//108
int fx_modify_global_variable (Actor* Owner, Actor* target, Effect* fx);//109
//10a unknown
int fx_protection_from_string (Actor* Owner, Actor* target, Effect* fx);//10b
int fx_explore_modifier (Actor* Owner, Actor* target, Effect* fx);//10c
int fx_screenshake (Actor* Owner, Actor* target, Effect* fx);//10d
int fx_unpause_caster (Actor* Owner, Actor* target, Effect* fx);//10e
//10f
int fx_apply_spell_on_condition (Actor* Owner, Actor* target, Effect* fx);//110
int fx_remove_area_effect (Actor* Owner, Actor* target, Effect* fx);//111
int fx_teleport_to_target (Actor* Owner, Actor* target, Effect* fx);//112
int fx_hide_in_shadows_modifier (Actor* Owner, Actor* target, Effect* fx);//113
int fx_detect_illusion_modifier (Actor* Owner, Actor* target, Effect* fx);//114
int fx_set_traps_modifier (Actor* Owner, Actor* target, Effect* fx);//115
int fx_to_hit_bonus_modifier (Actor* Owner, Actor* target, Effect* fx);//116
int fx_renable_button (Actor* Owner, Actor* target, Effect* fx);//117
int fx_force_surge_modifier (Actor* Owner, Actor* target, Effect* fx);//118
int fx_wild_surge_modifier (Actor* Owner, Actor* target, Effect* fx);//119
int fx_scripting_state (Actor* Owner, Actor* target, Effect* fx);//11a
int fx_apply_effect (Actor* Owner, Actor* target, Effect* fx);//11b
int fx_melee_to_hit_modifier (Actor* Owner, Actor* target, Effect* fx);//11c
int fx_melee_damage_modifier (Actor* Owner, Actor* target, Effect* fx);//11d
int fx_missile_damage_modifier (Actor* Owner, Actor* target, Effect* fx);//11e
int fx_no_circle_state (Actor* Owner, Actor* target, Effect* fx);//11f
int fx_fist_to_hit_modifier (Actor* Owner, Actor* target, Effect* fx);//120
int fx_fist_damage_modifier (Actor* Owner, Actor* target, Effect* fx);//121
int fx_title_modifier (Actor* Owner, Actor* target, Effect* fx);//122
int fx_disable_overlay_modifier (Actor* Owner, Actor* target, Effect* fx);//123
int fx_no_backstab_modifier (Actor* Owner, Actor* target, Effect* fx);//124
int fx_offscreenai_modifier (Actor* Owner, Actor* target, Effect* fx);//125
int fx_soundmn_modifier (Actor* Owner, Actor* target, Effect* fx);//126
int fx_disable_chunk_modifier (Actor* Owner, Actor* target, Effect* fx);//127
int fx_protection_from_animation (Actor* Owner, Actor* target, Effect* fx);//128
int fx_non_interruptible_modifier (Actor* Owner, Actor* target, Effect* fx);//129
int fx_area_switch (Actor* Owner, Actor* target, Effect* fx);//12a
int fx_chaos_shield_modifier (Actor* Owner, Actor* target, Effect* fx);//12b
int fx_deactivate_dead_modifier (Actor* Owner, Actor* target, Effect* fx);//12c
int fx_critical_hit_modifier (Actor* Owner, Actor* target, Effect* fx);//12d
int fx_can_use_any_item_modifier (Actor* Owner, Actor* target, Effect* fx);//12e
int fx_always_backstab_modifier (Actor* Owner, Actor* target, Effect* fx);//12f
int fx_mass_raise_dead (Actor* Owner, Actor* target, Effect* fx);//130
int fx_left_to_hit_modifier (Actor* Owner, Actor* target, Effect* fx);//131
//132
//133
int fx_stat195_modifier (Actor* Owner, Actor* target, Effect* fx);//134
int fx_modify_local_variable (Actor* Owner, Actor* target, Effect* fx);//135
int fx_timeless_modifier (Actor* Owner, Actor* target, Effect* fx);//136
//137
//138
//139
int fx_golem_stoneskin_modifier (Actor* Owner, Actor* target, Effect* fx);//13a
int fx_avatar_removal_modifier (Actor* Owner, Actor* target, Effect* fx);//13b
int fx_magical_rest (Actor* Owner, Actor* target, Effect* fx);//13c
int fx_improved_haste_state (Actor* Owner, Actor* target, Effect* fx);//13d

// FIXME: Make this an ordered list, so we could use bsearch!
static EffectRef effectnames[] = {
	{ "AcidResistanceModifier", fx_acid_resistance_modifier, 0 },
	{ "ACVsDamageTypeModifier", fx_ac_vs_damage_type_modifier, 0 },
	{ "AIIdentifierModifier", fx_ids_modifier, 0 },
	{ "AlchemyModifier", fx_alchemy_modifier, 0 },
	{ "Alignment:Change", fx_alignment_change, 0 },
	{ "Alignment:Invert", fx_alignment_invert, 0 },
	{ "AlwaysBackstab", fx_always_backstab_modifier, 0 },
	{ "AnimationIDModifier", fx_animation_id_modifier, 0 },
	{ "AttacksPerRoundModifier", fx_attacks_per_round_modifier, 0 },
	{ "BackstabModifier", fx_backstab_modifier, 0 },
	{ "BounceProjectile", fx_bounce_projectile, 0 },
	{ "ChangeName", fx_change_name, 0 },
	{ "ChaosShieldModifier", fx_chaos_shield_modifier, 0 },
	{ "CharismaModifier", fx_charisma_modifier, 0 },
	{ "ColdResistanceModifier", fx_cold_resistance_modifier, 0 },
	{ "Color:SetCharacterColorsByPalette", fx_set_color_gradient, 0 },
	{ "Color:SetCharacterColorsByRGB", fx_set_color_rgb, 0 },
	{ "ConstitutionModifier", fx_constitution_modifier, 0 },
	{ "CriticalHitModifier", fx_critical_hit_modifier, 0 },
	{ "CrushingResistanceModifier", fx_crushing_resistance_modifier, 0 },
	{ "Cure:Berserk", fx_cure_berserk_state, 0 },
	{ "Cure:Blind", fx_cure_blind_state, 0 },
	{ "Cure:Confusion", fx_cure_confused_state, 0 },
	{ "Cure:Deafness", fx_cure_deaf_state, 0 },
	{ "Cure:Death", fx_cure_dead_state, 0 },
	{ "Cure:Defrost", fx_cure_frozen_state, 0 },
	{ "Cure:Disease", fx_cure_diseased_state, 0 },
	{ "Cure:Feeblemind", fx_cure_feebleminded_state, 0 },
	{ "Cure:Hold", fx_cure_hold_state, 0 },
	{ "Cure:Infravision", fx_cure_infravision_state, 0 },
	{ "Cure:Invisible", fx_cure_invisible_state, 0 },
	{ "Cure:ImprovedInvisible", fx_cure_improved_invisible_state, 0 },
	{ "Cure:Nondetection", fx_cure_nondetection_state, 0 },
	{ "Cure:Panic", fx_cure_panic_state, 0 },
	{ "Cure:Petrification", fx_cure_petrified_state, 0 },
	{ "Cure:Poison", fx_cure_poisoned_state, 0 },
	{ "Cure:Sanctuary", fx_cure_sanctuary_state, 0 },
	{ "Cure:Silence", fx_cure_silenced_state, 0 },
	{ "Cure:Sleep", fx_cure_sleep_state, 0 },
	{ "Cure:Stun", fx_cure_stun_state, 0 },
	{ "CurrentHPModifier", fx_current_hp_modifier, 0 },
	{ "Damage", fx_damage, 0 },
	{ "DamageBonusModifier", fx_damage_bonus_modifier, 0 },
	{ "Death", fx_death, 0 },
	{ "DestroySelf", fx_destroy_self, 0 },
	{ "DexterityModifier", fx_dexterity_modifier, 0 },
	{ "DisableButton", fx_disable_button, 0 },  //sets disable button flag
	{ "DispelEffects", fx_dispel_effects, 0 },
	{ "DisplayString", fx_display_string, 0 },
	{ "ElectricityResistanceModifier", fx_electricity_resistance_modifier, 0 },
	{ "ExperienceModifier", fx_experience_modifier, 0 },
	{ "FatigueModifier", fx_fatigue_modifier, 0 },
	{ "FindTrapsModifier", fx_find_traps_modifier, 0 },
	{ "FireResistanceModifier", fx_fire_resistance_modifier, 0 },
	{ "FistDamageModifier", fx_fist_damage_modifier, 0 },
	{ "FistHitModifier", fx_fist_to_hit_modifier, 0 },
	{ "ForceSurgeModifier", fx_force_surge_modifier, 0 },
	{ "GoldModifier", fx_gold_modifier, 0 },
	{ "Icon:Disable", fx_disable_portrait_icon, 0 },
	{ "Icon:Display", fx_display_portrait_icon, 0 },
	{ "Icon:Remove", fx_remove_portrait_icon, 0 },
	{ "ImprovedHaste", fx_improved_haste_state, 0 },
	{ "IntelligenceModifier", fx_intelligence_modifier, 0 },
	{ "IntoxicationModifier", fx_intoxication_modifier, 0 },
	{ "Item:CreateDays", fx_create_item_days, 0 },
	{ "Item:CreateInSlot", fx_create_item_in_slot, 0 },
	{ "Item:CreateInventory", fx_create_inventory_item, 0 },
	{ "Item:CreateMagic", fx_create_magic_item, 0 },
	{ "Item:Remove", fx_remove_item, 0 },
	{ "Item:RemoveInventory", fx_remove_inventory_item, 0 },
	{ "KillCreatureType", fx_kill_creature_type, 0 },
	{ "LearnSpell", fx_learn_spell, 0 },
	{ "LevelModifier", fx_level_modifier, 0 },
	{ "LoreModifier", fx_lore_modifier, 0 },
	{ "LuckModifier", fx_luck_modifier, 0 },
	{ "MagicalColdResistanceModifier", fx_magical_cold_resistance_modifier, 0 },
	{ "MagicalFireResistanceModifier", fx_magical_fire_resistance_modifier, 0 },
	{ "MagicDamageResistanceModifier", fx_magic_damage_resistance_modifier, 0 },
	{ "MagicResistanceModifier", fx_magic_resistance_modifier, 0 },
	{ "MaximumHPModifier", fx_maximum_hp_modifier, 0 },
	{ "MeleeDamageModifier", fx_melee_damage_modifier, 0 },
	{ "MeleeHitModifier", fx_melee_to_hit_modifier, 0 },
	{ "MinimumHPModifier", fx_minimum_hp_modifier, 0 },
	{ "MiscastMagicModifier", fx_miscast_magic_modifier, 0 },
	{ "MissileDamageModifier", fx_missile_damage_modifier, 0 },
	{ "MissileHitModifier", fx_missile_to_hit_modifier, 0 },
	{ "MissilesResistanceModifier", fx_missiles_resistance_modifier, 0 },
	{ "MoraleBreakModifier", fx_morale_break_modifier, 0 },
	{ "NoCircleState", fx_no_circle_state, 0 },
	{ "OffhandHitModifier", fx_left_to_hit_modifier, 0 },
	{ "OpenLocksModifier", fx_open_locks_modifier, 0 },
	{ "Overlay:Entangle", fx_set_entangle_state, 0 },
	{ "Overlay:Grease", fx_set_grease_state, 0 },
	{ "Overlay:MinorGlobe", fx_set_minorglobe_state, 0 },
	{ "Overlay:Sanctuary", fx_set_sanctuary_state, 0 },
	{ "Overlay:ShieldGlobe", fx_set_shieldglobe_state, 0 },
	{ "Overlay:Web", fx_set_web_state, 0 },
	{ "MagicalRest", fx_magical_rest, 0 },
	{ "MoraleModifier", fx_morale_modifier, 0 },
	{ "MovementRate", fx_movement_modifier, 0 },    //fast
	{ "MovementModifier", fx_movement_modifier, 0 },//slow
	{ "Pausetarget", fx_pause_target, 0 }, //also known as casterhold
	{ "PickPocketsModifier", fx_pick_pockets_modifier, 0 },
	{ "PiercingResistanceModifier", fx_piercing_resistance_modifier, 0 },
	{ "PlayMovie", fx_play_movie, 0 },
	{ "PlaySound", fx_playsound, 0 },
	{ "PlayVisualEffect", fx_play_visual_effect, 0 },
	{ "PriestSpellSlotsModifier", fx_bonus_priest_spells, 0 },
	{ "PortraitChange", fx_portrait_change, 0 },
	{ "PowerWordKill", fx_power_word_kill, 0 },
	{ "Proficiency", fx_proficiency, 0 },
	{ "Protection:Creature", fx_generic_effect, 0 },
	{ "Protection:Opcode", fx_generic_effect, 0 },
	{ "Protection:SpellLevel",fx_generic_effect,0},//overlay?
	{ "RemoveCurse", fx_remove_curse, 0 },
	{ "RenableButton", fx_renable_button, 0 },  //removes disable button flag
	{ "ReputationModifier", fx_reputation_modifier, 0 },
	{ "RestoreSpells", fx_restore_spell_level, 0 },
	{ "SaveVsBreathModifier", fx_save_vs_breath_modifier, 0 },
	{ "SaveVsDeathModifier", fx_save_vs_death_modifier, 0 },
	{ "SaveVsPolyModifier", fx_save_vs_poly_modifier, 0 },
	{ "SaveVsSpellsModifier", fx_save_vs_spell_modifier, 0 },
	{ "SaveVsWandsModifier", fx_save_vs_wands_modifier, 0 },
	{ "ScriptingState", fx_scripting_state, 0 },
	{ "Sequencer:Activate", fx_activate_spell_sequencer, 0 },
	{ "Sequencer:Create", fx_create_spell_sequencer, 0 },
	{ "Sequencer:Store", fx_store_spell_sequencer, 0 },
	{ "SetAIScript", fx_set_ai_script, 0 },
	{ "SexModifier", fx_sex_modifier, 0 },
	{ "SlashingResistanceModifier", fx_slashing_resistance_modifier, 0 },
	{ "SlowPoisonDamageRate", fx_generic_effect, 0 }, //slow poison effect
	{ "Sparkle", fx_sparkle, 0 },
	{ "SpellDurationModifier", fx_spell_duration_modifier, 0 },
	{ "State:Berserk", fx_set_berserk_state, 0 },
	{ "State:Blind", fx_set_blind_state, 0 },
	{ "State:Blur", fx_set_blur_state, 0 },
	{ "State:Charmed", fx_set_charmed_state, 0 },
	{ "State:Confused", fx_set_confused_state, 0 },
	{ "State:Deafness", fx_set_deaf_state, 0 },
	{ "State:Diseased", fx_set_diseased_state, 0 },
	{ "State:Feeblemind", fx_set_feebleminded_state, 0 },
	{ "State:Hasted", fx_set_hasted_state, 0 },
	{ "State:Hold", fx_hold_creature, 0 }, //175
	{ "State:Hold2", fx_hold_creature, 0 },//185
	{ "State:Hold3", fx_hold_creature_no_icon, 0 }, //109
	{ "State:Infravision", fx_set_infravision_state, 0 },
	{ "State:Invisible", fx_set_invisible_state, 0 }, //both invis or improved invis
	{ "State:Nondetection", fx_set_nondetection_state, 0 },
	{ "State:Panic", fx_set_panic_state, 0 },
	{ "State:Petrification", fx_set_petrified_state, 0 },
	{ "State:Poisoned", fx_set_poisoned_state, 0 },
	{ "State:Silenced", fx_set_silenced_state, 0 },
	{ "State:Helpless", fx_set_unconscious_state, 0 },
	{ "State:Slowed", fx_set_slowed_state, 0 },
	{ "State:Stun", fx_set_stun_state, 0 },
	{ "StealthModifier", fx_stealth_modifier, 0 },
	{ "StoneSkinModifier", fx_stoneskin_modifier, 0 },
	{ "StoneSkin2Modifier", fx_golem_stoneskin_modifier, 0 },
	{ "StrengthModifier", fx_strength_modifier, 0 },
	{ "StrengthBonusModifier", fx_strength_bonus_modifier, 0 },
	{ "SummonCreature", fx_summon_creature, 0 },
	{ "ToHitModifier", fx_to_hit_modifier, 0 },
	{ "ToHitBonusModifier", fx_to_hit_bonus_modifier, 0 },
	{ "TimelessState", fx_timeless_modifier, 0 },
	{ "TrackingModifier", fx_tracking_modifier, 0 },
	{ "TransparencyModifier", fx_transparency_modifier, 0 },
	{ "UnsummonCreature", fx_unsummon_creature, 0 },
	{ "Variable:StoreLocalVariable", fx_local_variable, 0 },
	{ "VisualRangeModifier", fx_visual_range_modifier, 0 },
	{ "WildSurgeModifier", fx_wild_surge_modifier, 0 },
	{ "WisdomModifier", fx_wisdom_modifier, 0 },
	{ "WizardSpellSlotsModifier", fx_bonus_wizard_spells, 0 },
	{ NULL, NULL, 0 },
};


FXOpc::FXOpc(void)
{
	core->RegisterOpcodes( sizeof( effectnames ) / sizeof( EffectRef ) - 1, effectnames );
}

FXOpc::~FXOpc(void)
{
}

bool FXOpc::Init(void)
{
	return true;
}

// Helper macros and functions for effect opcodes
/*
#define CHECK_LEVEL() { \
	int level = target->GetXPLevel( true ); \
	if ((fx->DiceSides != 0 || fx->DiceThrown != 0) && (level < (int)fx->DiceSides || level > (int)fx->DiceThrown)) \
		return FX_NOT_APPLIED; \
	}
*/

bool match_ids(Actor *target, int table, ieDword value)
{
	if (value == 0) {
		return true;
	}

	int a, stat;

	switch (table) {
		case 2: //EA
			stat = IE_EA; break;
		case 3: //GENERAL
			stat = IE_GENERAL; break;
		case 4: //RACE
			stat = IE_RACE; break;
		case 5: //CLASS
			stat = IE_CLASS; break;
		case 6: //SPECIFIC
			stat = IE_SPECIFIC; break;
		case 7: //GENDER
			stat = IE_SEX; break;
		case 8: //ALIGNMENT
			stat = target->GetStat(IE_ALIGNMENT);
			a = value&15;
			if (a) {
				if (a != ( stat & 15 )) {
					return false;
				}
			}
			a = value & 240;
			if (a) {
				if (a != ( stat & 240 )) {
					return false;
				}
			}
			return true;
		default:
			return false;
	}
	if (target->GetStat(stat)==value) {
		return true;
	}
	return false;
}

// Effect opcodes
// FIXME: These should be moved into their own plugins
// NOTE: These opcode numbers are true for PS:T and are meant just for 
// better orientation
// <avenger> opcodes below 0xb0 are the same for ALL variations (or crash/nonfunctional)
// so we can implement those without fear, overlapping functions could be marked
// like 0xb1 (pst), and the effect.ids file points to the appropriate function

// 0x00
int fx_ac_vs_damage_type_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_ac_vs_damage_type_modifier (%2d): AC Modif: %d ; Type: %d ; MinLevel: %d ; MaxLevel: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2, (int) fx->DiceSides, (int) fx->DiceThrown );
	//check level was pulled outside as a common functionality
	//CHECK_LEVEL();

	// it is a bitmask
	int type = fx->Parameter2;
	if (type == 0) {
		// FIXME: this is probably wrong, but it's hack to see
		// anything in PST
		STAT_ADD( IE_ARMORCLASS, fx->Parameter1 );
		type = 15;
	}

	//the original engine did work with the combination of these bits
	//but since it crashed, we are not bound to the same rules
	if (type & 1) STAT_ADD( IE_ACCRUSHINGMOD, fx->Parameter1 );
	if (type & 2) STAT_ADD( IE_ACMISSILEMOD, fx->Parameter1 );
	if (type & 4) STAT_ADD( IE_ACPIERCINGMOD, fx->Parameter1 );
	if (type & 8) STAT_ADD( IE_ACSLASHINGMOD, fx->Parameter1 );

	// FIXME: set to Param1 or Param1-1 ?
	if (type == 16 && target->Modified[IE_ARMORCLASS] > fx->Parameter1)
		STAT_SET( IE_ARMORCLASS, fx->Parameter1 );

	return FX_APPLIED;
}

// 0x01
int fx_attacks_per_round_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_attacks_per_round_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD( IE_NUMBEROFATTACKS);
	return FX_APPLIED;
}

// 0x02
// this effect clears the STATE_SLEEP (1) bit, but clearing it alone wouldn't remove the
// unconscious effect, which is combined with STATE_HELPLESS (0x20+1)
int fx_cure_sleep_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_sleep_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_CURE( STATE_SLEEP );
	return FX_NOT_APPLIED;
}

// 0x03
// this effect clears the STATE_BERSERK (2) bit, but bg2 actually ignores the bit
EffectRef fx_set_berserk_state_ref={"State:Berserk",NULL,-1};

int fx_cure_berserk_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_berserk_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_CURE( STATE_BERSERK );
	target->fxqueue.RemoveAllEffects(fx_set_berserk_state_ref);
	return FX_NOT_APPLIED;
}

// 0x04
// this effect sets the STATE_BERSERK bit, but bg2 actually ignores the bit
int fx_set_berserk_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_berserk_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_SET( STATE_BERSERK );
	return FX_NOT_APPLIED;
}

// 0x05 charm
int fx_set_charmed_state (Actor* Owner, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_charmed_state (%2d): General: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	if (STAT_GET(IE_GENERAL)!=fx->Parameter1) {
		return FX_NOT_APPLIED;
	}
	bool enemyally = Owner->GetStat(IE_EA)>EA_GOODCUTOFF;

	switch (fx->Parameter2) {
	case 0: //charmed (target neutral after charm)
		core->DisplayConstantStringName(STR_CHARMED, 0xff0000, target);
	case 1000:
		break;
	case 1: //charmed (target hostile after charm)
		core->DisplayConstantStringName(STR_CHARMED, 0xff0000, target);
	case 1001:
		target->SetBase(IE_EA, EA_ENEMY);
		break;
	case 2: //dire charmed (target neutral after charm)
		core->DisplayConstantStringName(STR_DIRECHARMED, 0xff0000, target);
	case 1002:
		break;
	case 3: //dire charmed (target hostile after charm)
		core->DisplayConstantStringName(STR_DIRECHARMED, 0xff0000, target);
	case 1003:
		target->SetBase(IE_EA, EA_ENEMY);
		break;
	case 4: //controlled by cleric
		core->DisplayConstantStringName(STR_CONTROLLED, 0xff0000, target);
	case 1004:
		target->SetBase(IE_EA, EA_ENEMY);
		break;
	case 5: //thrullcharm?
		core->DisplayConstantStringName(STR_CHARMED, 0xff0000, target);
	case 1005:
		STAT_SET(IE_EA, EA_ENEMY );
		return FX_PERMANENT;
	}

	STATE_SET( STATE_CHARMED );
	STAT_SET( IE_EA, enemyally?EA_ENEMY:EA_CHARMED );
	//don't stick if permanent
	return FX_PERMANENT;
}

// 0x06
int fx_charisma_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_charisma_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	if (fx->TimingMode==FX_DURATION_INSTANT_PERMANENT) {
		BASE_MOD( IE_CHR );
	} else {
		STAT_MOD( IE_CHR );
	}
	return FX_PERMANENT;
}

// 0x07
// this effect might not work in pst, they don't have separate weapon slots
int fx_set_color_gradient (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_color_gradient (%2d): Gradient: %d, Location: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	target->SetColor( fx->Parameter2, fx->Parameter1 );
	return FX_APPLIED;
}

int fx_set_color_rgb (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_color_rgb (%2d): RGB: %x, Location: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	target->SetColor( fx->Parameter2, fx->Parameter1 | 0xff000000 );
	return FX_APPLIED;
}

// 0x0A
int fx_constitution_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_constitution_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	if (fx->TimingMode==FX_DURATION_INSTANT_PERMANENT) {
		BASE_MOD( IE_CON );
	} else {
		STAT_MOD( IE_CON );
	}
	return FX_PERMANENT;
}

// 0x0B
EffectRef fx_poisoned_state_ref={"State:Poison",NULL,-1};

int fx_cure_poisoned_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_poisoned_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_CURE( STATE_POISONED ); //this actually isn't in the engine code, i think
	target->fxqueue.RemoveAllEffects( fx_poisoned_state_ref ); //this is what actually happens in bg2
	return FX_NOT_APPLIED;
}

// 0x0C Damage
// this is a very important effect
int fx_damage (Actor* Owner, Actor* target, Effect* fx)
{
	if (0) printf( "fx_damage (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	int damage; //FIXME damage calculation, random damage, etc

	damage = 1;
	damage = target->Damage(damage, fx->Parameter2, Owner); //FIXME!
	//handle invulnerabilities, print damage caused
	//this effect doesn't stick
	return FX_NOT_APPLIED;
}

//0x0D
int fx_death (Actor* Owner, Actor* target, Effect* fx)
{
	if (0) printf( "fx_death (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	target->Damage(0, fx->Parameter2, Owner); //hmm?
	//death has damage type too
	target->Die(Owner);
	//this effect doesn't stick
	return FX_NOT_APPLIED;
}

// 0xE
int fx_cure_frozen_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_frozen_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_CURE( STATE_FROZEN );
	return FX_NOT_APPLIED;
}

// 0x0F
int fx_dexterity_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_dexterity_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	if (fx->TimingMode==FX_DURATION_INSTANT_PERMANENT) {
		BASE_MOD( IE_DEX );
	} else {
		STAT_MOD( IE_DEX );
	}
	return FX_PERMANENT;
}

// 0x10
// this function removes slowed state, or sets hasted state
int fx_set_hasted_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_hasted_state (%2d): Type: %d\n", fx->Opcode, fx->Parameter2 );
	switch (fx->Parameter2) {
	case 0: //normal haste
		if ( STATE_GET(STATE_SLOWED) ) {
			STATE_CURE( STATE_SLOWED );
		} else {
			STATE_SET( STATE_HASTED );
		}
		break;
	case 1://improved haste
		if ( STATE_GET(STATE_SLOWED) ) {
			STATE_CURE( STATE_SLOWED );
		} else {
			STATE_SET( STATE_HASTED );
		}
		break;
	case 2://speed haste only
		break;
	}
	//probably when this effect expires, it issues a set_slowed_state?
	return FX_NOT_APPLIED;
}

// 0x11
int fx_current_hp_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_current_hp_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_HITPOINTS );
	return FX_APPLIED;
}

// 0x12
int fx_maximum_hp_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_maximum_hp_modifier (%2d): Stat Modif: %d ; Modif Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	int bonus;

	switch (fx->Parameter2) {
	case 0:
		bonus = DICE_ROLL( (signed)fx->Parameter1 );
		STAT_ADD( IE_MAXHITPOINTS, bonus );
		STAT_ADD( IE_HITPOINTS, bonus );
		break;
	case 1:
		STAT_SET( IE_MAXHITPOINTS, fx->Parameter1 );
		STAT_SET( IE_HITPOINTS, fx->Parameter1 );
		break;
	case 2:
		STAT_MUL( IE_MAXHITPOINTS, fx->Parameter1 );
		STAT_MUL( IE_HITPOINTS, fx->Parameter1 );
		break;
	case 3:
		bonus = DICE_ROLL( (signed)fx->Parameter1 );
		STAT_ADD( IE_MAXHITPOINTS, bonus );
		break;
	case 4:
		STAT_SET( IE_MAXHITPOINTS, fx->Parameter1 );
		break;
	case 5:
		STAT_MUL( IE_MAXHITPOINTS, fx->Parameter1 );
		break;
	}
	return FX_APPLIED;
}

// 0x13
int fx_intelligence_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_intelligence_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	if (fx->TimingMode==FX_DURATION_INSTANT_PERMANENT) {
		BASE_MOD( IE_INT );
	} else {
		STAT_MOD( IE_INT );
	}
	return FX_PERMANENT;
}

// 0x14
// this is more complex, there is a half-invisibility state
// and there is a hidden state
int fx_set_invisible_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	switch (fx->Parameter2) {
		case 1:
			STATE_SET( STATE_INVISIBLE );
			break;
		case 2:
			STATE_SET( STATE_INVIS2 );
			break;
	}
	return FX_APPLIED;
}

// 0x15
int fx_lore_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_lore_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_LORE );
	return FX_APPLIED;
}

// 0x16
int fx_luck_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_luck_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_LUCK );
	return FX_APPLIED;
}

// 0x17
int fx_morale_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_morale_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_MORALE );
	return FX_APPLIED;
}

// 0x18
int fx_set_panic_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_panic_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	//shall we set morale to 0 or just flick the panic flag on
	//this requires a little research
	STATE_SET( STATE_PANIC );
	//target->NewStat( IE_MORALE, 0, fx->Parameter2 );
	return FX_NOT_APPLIED;
}

#define POISON_PERCENT 0
#define POISON_SECONDS 1
#define POISON_POINTS  2
// 0x19
int fx_set_poisoned_state (Actor* Owner, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_poisoned_state (%2d): Damage: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	//apparently this bit isn't set, but then why is it here
	//this requires a little research
	STATE_SET( STATE_POISONED );
	//also this effect is executed every update
	ieDword damage;

	switch(fx->Parameter2)
	{
	case POISON_PERCENT:
		damage = target->GetStat(IE_MAXHITPOINTS) * fx->Parameter1 / 100;
		break;
	case POISON_SECONDS:
		damage = 1;
		if (fx->Parameter1 && (core->GetGame()->GameTime%fx->Parameter1)) {
			return FX_APPLIED;
		}
		break;
	case POISON_POINTS:
		damage = fx->Parameter1;
		break;
	default:
		damage = 1;
		break;
	}
	//percent
	target->Damage(damage, DAMAGE_POISON, Owner);
	return FX_APPLIED;
}


// 0x1a
// gemrb extension: if the resource field is filled, it will remove curse only from the specified item
int fx_remove_curse (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_remove_curse (%2d): Resource: %s\n", fx->Opcode, fx->Resource );

	int i = target->inventory.GetSlotCount();
	while(i--) {
		//does this slot need unequipping
		if (core->QuerySlotEffects(i) ) {
			if (fx->Resource[0] && strnicmp(target->inventory.GetSlotItem(i)->ItemResRef, fx->Resource,8) ) {
				continue;
			}
			target->inventory.UnEquipItem(i,true);
		}
	}
	//this could also be done, but not implemented yet
	//target->inventory.ChangeItemFlag(fx->Resource, IE_INV_ITEM_CURSED, BF_NAND);
	//this is an instant effect
	return FX_NOT_APPLIED;
}

// 0x1b
int fx_acid_resistance_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_acid_resistance_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_RESISTACID );
	return FX_APPLIED;
}

// 0x1c
int fx_cold_resistance_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cold_resistance_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_RESISTCOLD );
	return FX_APPLIED;
}

// 0x1d
int fx_electricity_resistance_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_electricity_resistance_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_RESISTELECTRICITY );
	return FX_APPLIED;
}

// 0x1e
int fx_fire_resistance_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_fire_resistance_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_RESISTFIRE );
	return FX_APPLIED;
}

// 0x1f
int fx_magic_damage_resistance_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_magic_damage_resistance_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_MAGICDAMAGERESISTANCE );
	return FX_APPLIED;
}

// 0x20
int fx_cure_dead_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_dead_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	//someone should clear the internal flags related to death
	STATE_CURE( STATE_DEAD );
	return FX_NOT_APPLIED;
}

// 0x21
int fx_save_vs_death_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_save_vs_death_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_SAVEVSDEATH );
	return FX_APPLIED;
}

// 0x22
int fx_save_vs_wands_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_save_vs_wands_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_SAVEVSWANDS );
	return FX_APPLIED;
}

// 0x23
int fx_save_vs_poly_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_save_vs_poly_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_SAVEVSPOLY );
	return FX_APPLIED;
}

// 0x24
int fx_save_vs_breath_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_save_vs_breath_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_SAVEVSBREATH );
	return FX_APPLIED;
}

// 0x25
int fx_save_vs_spell_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_save_vs_spell_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_SAVEVSSPELL );
	return FX_APPLIED;
}

// 0x26
int fx_set_silenced_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_silenced_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_SET( STATE_SILENCED );
	return FX_NOT_APPLIED;
}

// 0x27
// this effect sets both bits, but 'awaken' only removes the sleep bit
int fx_set_unconscious_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_unconscious_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_SET( STATE_HELPLESS | STATE_SLEEP );
	//the effect directly sets the state bit, and doesn't stick
	return FX_NOT_APPLIED;
}

// 0x28
// this function removes hasted state, or sets slowed state
int fx_set_slowed_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_slowed_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	if (STATE_GET(STATE_HASTED) ) {
		STATE_CURE( STATE_HASTED );
	} else {
		STATE_SET( STATE_SLOWED );
	}
	return FX_NOT_APPLIED;
}

// 0x29
int fx_sparkle (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_sparkle (%2d): Sparkle colour: %d ; Sparkle type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	target->GetCurrentArea()->Sparkle( fx->Parameter1, fx->Parameter2);
	return FX_NOT_APPLIED;
}

// 0x2A
int fx_bonus_wizard_spells (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_bonus_wizard_spells (%2d): Spell Add: %d ; Spell Level: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	
	int i=1;
	for( int j=0;j<9;j++) {
		if (fx->Parameter2&i) {
			target->spellbook.SetMemorizableSpellsCount(fx->Parameter1, IE_SPELL_TYPE_WIZARD, j, true);
		}
		i<<=1;
	}
	return FX_APPLIED;
}

// 0x2B
int fx_cure_petrified_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_petrified_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_CURE( STATE_PETRIFIED );
	return FX_NOT_APPLIED;
}

// 0x2C
int fx_strength_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_strength_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	if (fx->TimingMode==FX_DURATION_INSTANT_PERMANENT) {
		BASE_MOD( IE_STR );
	} else {
		STAT_MOD( IE_STR );
	}
	return FX_PERMANENT;
}

// 0x2D
int fx_set_stun_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_stun_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_SET( STATE_STUNNED );
	return FX_NOT_APPLIED;
}

// 0x2E
EffectRef fx_set_stun_state_ref={"State:Stun",NULL,-1};

int fx_cure_stun_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_stun_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_CURE( STATE_STUNNED );
	target->fxqueue.RemoveAllEffects(fx_set_stun_state_ref);
	return FX_NOT_APPLIED;
}

// 0x2F
EffectRef fx_set_invisible_state_ref={"State:Invisible",NULL,-1};

int fx_cure_invisible_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_invisible_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_CURE( STATE_INVISIBLE );
	target->fxqueue.RemoveAllEffects(fx_set_invisible_state_ref);
	return FX_NOT_APPLIED;
}

// 0x30
EffectRef fx_set_silenced_state_ref={"State:Silence",NULL,-1};

int fx_cure_silenced_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_silenced_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_CURE( STATE_SILENCED );
	target->fxqueue.RemoveAllEffects(fx_set_silenced_state_ref);
	return FX_NOT_APPLIED;
}

// 0x31
int fx_wisdom_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_wisdom_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	if (fx->TimingMode==FX_DURATION_INSTANT_PERMANENT) {
		BASE_MOD( IE_WIS );
	} else {
		STAT_MOD( IE_WIS );
	}
	return FX_PERMANENT;
}

// 0x32
int fx_rgb_pulsate (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	if (0) printf( "fx_rgb_pulsate (%2d): RGB: %d, Location and speed: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	return FX_APPLIED;
}
// 0x33
int fx_rgb_darken (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	if (0) printf( "fx_rgb_darken (%2d): RGB: %d, Location and speed: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	return FX_APPLIED;
}
// 0x34
int fx_rgb_glow (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	if (0) printf( "fx_rgb_glow (%2d): RGB: %d, Location and speed: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	return FX_APPLIED;
}
// 0x35
int fx_animation_id_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_animation_id_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_ANIMATION_ID );
	return FX_APPLIED;
}

// 0x36
int fx_to_hit_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_to_hit_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_TOHIT );
	return FX_APPLIED;
}

// 0x37 instant kill of creature type
int fx_kill_creature_type (Actor* Owner, Actor* target, Effect* fx)
{
	if (0) printf( "fx_kill_creature_type (%2d): Value: %d, IDS: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	if (match_ids( target, fx->Parameter1, fx->Parameter2) ) {
		target->Die( Owner );
	}
	//need research (is this an instant action or sticks)
	return FX_NOT_APPLIED;
}

// 0x38
//switch good to evil and evil to good
static int gne_toggle[4]={0,3,2,1};

int fx_alignment_invert (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_alignment_invert (%2d)\n", fx->Opcode );
	ieDword newalign = target->GetStat( IE_ALIGNMENT );
	newalign = (newalign & AL_LNC_MASK) + gne_toggle[newalign & AL_GNE_MASK];
	STAT_SET( IE_ALIGNMENT, newalign );
	//target->SetStat( IE_ALIGNMENT, newalign, false );
	return FX_APPLIED;
}

// 0x39
int fx_alignment_change (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_alignment_change (%2d): Value: %d\n", fx->Opcode, fx->Parameter2 );
	STAT_SET( IE_ALIGNMENT, fx->Parameter2 );
	//target->SetStat( IE_ALIGNMENT, fx->Parameter2, false );
	return FX_APPLIED;
}

//0x3A

int fx_dispel_effects (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_dispel_effects (%2d): Value: %d, IDS: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	ieDword level = fx->Power;

	//this might be different, it could be that removal depends on random
	if (fx->Parameter2==1) {
		level = fx->Parameter1;
	}
	target->fxqueue.RemoveLevelEffects(level, true);
	return FX_NOT_APPLIED;
}

// 0x3B
int fx_stealth_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_stealth_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_STEALTH );
	return FX_APPLIED;
}

// 0x3C
int fx_miscast_magic_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_miscast_magic_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	switch (fx->Parameter2) {
		case 0:
			target->NewStat( IE_SPELLFAILUREMAGE, fx->Parameter1, MOD_ABSOLUTE);
			break;
		case 1:
			target->NewStat( IE_SPELLFAILUREPRIEST, fx->Parameter1, MOD_ABSOLUTE);
			break;
		default:
			return FX_NOT_APPLIED;
	}
	return FX_APPLIED;
}

// 0x3D
// this crashes in bg2
// and in iwd it doesn't really follow the stat_mod convention
int fx_alchemy_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_alchemy_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_ALCHEMY );
	return FX_APPLIED;
}

// 0x3E
int fx_bonus_priest_spells (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_bonus_priest_spells (%2d): Spell Add: %d ; Spell Level: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	
	int i=1;
	for( int j=0;j<9;j++) {
		if (fx->Parameter2&i) {
			target->spellbook.SetMemorizableSpellsCount(fx->Parameter1, IE_SPELL_TYPE_PRIEST, j, true);
		}
		i<<=1;
	}
	return FX_APPLIED;
}

// 0x3F
int fx_set_infravision_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_infravision_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_SET( STATE_INFRA );
	return FX_APPLIED;
}

// 0x40
EffectRef fx_set_infravision_state_ref={"State:Infravision",NULL,-1};

int fx_cure_infravision_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_infravision_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_CURE( STATE_INFRA );
	target->fxqueue.RemoveAllEffects(fx_set_infravision_state_ref);
	return FX_NOT_APPLIED;
}

//0x41
int fx_set_blur_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_blur_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_SET( STATE_BLUR );
	return FX_NOT_APPLIED;
}

// 0x42
int fx_transparency_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_transparency_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_TRANSLUCENT );
	return FX_APPLIED;
}

// 0x43
int fx_summon_creature (Actor* Owner, Actor* target, Effect* fx)
{
	if (0) printf( "fx_summon_creature (%2d): ResRef:%s Anim:%s Type: %d\n", fx->Opcode, fx->Resource, fx->Resource2, fx->Parameter2 );

	//check the summoning limit?
	DataStream* ds = core->GetResourceMgr()->GetResource( fx->Resource, IE_CRE_CLASS_ID );
	Actor *ab = core->GetCreature(ds);
	if (!ab) {
		return FX_NOT_APPLIED;
	}

	ab->LastSummoner = Owner->GetID();

	switch (fx->Parameter2) {
		case 0: case 1: case 3:
			ab->SetBase(IE_EA, EA_ALLY); //is this the summoned EA?
			break;
		case 5:
			ab->SetBase(IE_EA, EA_ENEMY);
			break;
		default:
			break;
	}

	//probably we should use the position in fx (and set it earlier)
	Point position = target->Pos;
	//
	//
	Map *map = target->GetCurrentArea();
	ab->SetPosition(map, position, true, 0);
	if (fx->Resource2[0]) {
		Point p(0,0);
		ScriptedAnimation* vvc = core->GetScriptedAnimation(fx->Resource2, p, 0);
		map->AddVVCCell( vvc );
	}

	return FX_NOT_APPLIED;
}

//0x44
int fx_unsummon_creature (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_unsummon_creature (%2d)\n", fx->Opcode );

	if (target->LastSummoner) {
		//animation
		target->DestroySelf();
	}
	return FX_NOT_APPLIED;
}

// 0x45
int fx_set_nondetection_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_nondetection_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_SET( STATE_NONDET );
	return FX_PERMANENT;
}

// 0x46
int fx_cure_nondetection_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_nondetection_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_CURE( STATE_NONDET );
	return FX_NOT_APPLIED;
}

//0x47
int fx_sex_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_sex_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD( IE_SEX );
	return FX_APPLIED;
}

//0x48
int fx_ids_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_ids_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	switch (fx->Parameter2) {
	case 0:
		STAT_SET(IE_EA, fx->Parameter1);
		break;
	case 1:
		STAT_SET(IE_GENERAL, fx->Parameter1);
		break;
	case 2:
		STAT_SET(IE_RACE, fx->Parameter1);
		break;
	case 3:
		STAT_SET(IE_CLASS, fx->Parameter1);
		break;
	case 4:
		STAT_SET(IE_SPECIFIC, fx->Parameter1);
		break;
	case 5:
		STAT_SET(IE_SEX, fx->Parameter1);
		break;
	case 6:
		STAT_SET(IE_ALIGNMENT, fx->Parameter1);
		break;
	default:
		return FX_NOT_APPLIED;
	}
	//not sure, need a check
	return FX_APPLIED;
}

// 0x49
int fx_damage_bonus_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_damage_bonus_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_DAMAGEBONUS );
	return FX_APPLIED;
}

// 0x4a
int fx_set_blind_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_blind_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_SET( STATE_BLIND );
	return FX_APPLIED;
}

// 0x4b
EffectRef fx_set_blind_state_ref={"State:Blind",NULL,-1};

int fx_cure_blind_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_blind_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_CURE( STATE_BLIND );
	target->fxqueue.RemoveAllEffects(fx_set_blind_state_ref);
	return FX_NOT_APPLIED;
}

// 0x4c
int fx_set_feebleminded_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_feebleminded_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_SET( STATE_FEEBLE );
	return FX_NOT_APPLIED;
}

// 0x4d
EffectRef fx_set_feebleminded_state_ref={"State:Feeblemind",NULL,-1};
int fx_cure_feebleminded_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_feebleminded_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_CURE( STATE_FEEBLE );
	target->fxqueue.RemoveAllEffects(fx_set_feebleminded_state_ref);
	return FX_NOT_APPLIED;
}

//0x4f
int fx_set_diseased_state (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	if (0) printf( "fx_set_diseased_state (%2d): Damage: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	//STATE_SET( STATE_DISEASED ); //no this we don't want
	//also this effect is executed every update
	return FX_APPLIED;
}


EffectRef fx_diseased_state_ref={"State:Disease",NULL,-1};

//apparently this effect removes effect 0x4e (78)
int fx_cure_diseased_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_diseased_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	//STATE_CURE( STATE_DISEASED ); //the bit flagged as disease is actually the active state. so this is even more unlikely to be used as advertised
	target->fxqueue.RemoveAllEffects( fx_diseased_state_ref ); //this is what actually happens in bg2
	return FX_NOT_APPLIED;
}

// 0x50
//this state has no bit???
int fx_set_deaf_state (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	if (0) printf( "fx_set_deaf_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	return FX_APPLIED;
}

// 0x51
EffectRef fx_deaf_state_ref={"State:Deaf",NULL,-1};

//removes the deaf effect
int fx_cure_deaf_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_deaf_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	
	target->fxqueue.RemoveAllEffects(fx_deaf_state_ref);
	return FX_NOT_APPLIED;
}

//0x52
int fx_set_ai_script (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_ai_state (%2d): Resource: %s, Type: %d\n", fx->Opcode, fx->Resource, fx->Parameter2 );
	target->SetScript (fx->Resource, fx->Parameter2);
	return FX_NOT_APPLIED;
}

//0x53
int fx_protection_from_projectile (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_bounce_projectile (%2d): Type: %d\n", fx->Opcode, fx->Parameter2 );
	STAT_SET( IE_SHIELDGLOBE, 1 );
	return FX_APPLIED;
}

// 0x54
int fx_magical_fire_resistance_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_magical_fire_resistance_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_RESISTMAGICFIRE );
	return FX_APPLIED;
}

// 0x55
int fx_magical_cold_resistance_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_magical_cold_resistance_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_RESISTMAGICCOLD );
	return FX_APPLIED;
}

// 0x56
int fx_slashing_resistance_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_slashing_resistance_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_RESISTSLASHING );
	return FX_APPLIED;
}

// 0x57
int fx_crushing_resistance_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_crushing_resistance_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_RESISTCRUSHING );
	return FX_APPLIED;
}

// 0x58
int fx_piercing_resistance_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_piercing_resistance_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_RESISTPIERCING );
	return FX_APPLIED;
}

// 0x59
int fx_missiles_resistance_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_missiles_resistance_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_RESISTMISSILE );
	return FX_APPLIED;
}

// 0x5A
int fx_open_locks_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_open_locks_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_LOCKPICKING );
	return FX_APPLIED;
}

// 0x5B
int fx_find_traps_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_find_traps_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_TRAPS );
	return FX_APPLIED;
}

// 0x5C
int fx_pick_pockets_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_pick_pockets_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_PICKPOCKET );
	return FX_APPLIED;
}

// 0x5D
int fx_fatigue_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_fatigue_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_FATIGUE );
	return FX_APPLIED;
}

// 0x5E
int fx_intoxication_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_intoxication_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_INTOXICATION );
	return FX_APPLIED;
}

// 0x5F
int fx_tracking_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_tracking_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_TRACKING );
	return FX_APPLIED;
}

// 0x60
int fx_level_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_level_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_LEVEL );
	return FX_APPLIED;
}

// 0x61
int fx_strength_bonus_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_strength_bonus_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_STREXTRA );
	return FX_APPLIED;
}

// 0x62
int fx_state_regeneration (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_state_regeneration (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	int damage;

	switch(fx->Parameter2)
	{
	case POISON_PERCENT:
		damage = target->GetStat(IE_MAXHITPOINTS) * fx->Parameter1 / 100;
		break;
	case POISON_SECONDS:
		damage = 1;
		if (fx->Parameter1 && (core->GetGame()->GameTime%fx->Parameter1)) {
			return FX_APPLIED;
		}
		break;
	case POISON_POINTS:
		damage = fx->Parameter1;
		break;
	default:
		damage = 1;
		break;
	}
	
	STAT_ADD( IE_HITPOINTS, damage );
	return FX_APPLIED;
}
// 0x63
int fx_spell_duration_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_spell_duration_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	switch (fx->Parameter2) {
		case 0:
			target->NewStat( IE_SPELLDURATIONMODMAGE, fx->Parameter1, MOD_ABSOLUTE);
			break;
		case 1:
			target->NewStat( IE_SPELLDURATIONMODPRIEST, fx->Parameter1, MOD_ABSOLUTE);
			break;
		default:
			return FX_NOT_APPLIED;
	}
	return FX_APPLIED;
}

// 0x64, 65, 66
int fx_generic_effect (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	if (0) printf( "fx_generic_effect (%2d): Param1: %d, Param2: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	return FX_APPLIED;
}

//0x67
int fx_change_name (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_change_name_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	target->SetText(fx->Parameter1, 0);
	return FX_NOT_APPLIED; //???
}

//0x68
int fx_experience_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_experience_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	//i believe this has mode too
	target->AddExperience (fx->Parameter1);
	return FX_NOT_APPLIED;
}

//0x69
int fx_gold_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_gold_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	if (!target->InParty) {
		STAT_MOD( IE_GOLD );
		return FX_NOT_APPLIED;
	}
	ieDword gold;
	Game *game = core->GetGame();
	//for party members, the gold is stored in the game object
	switch( fx->Parameter2) {
		case MOD_ADDITIVE:
			gold = fx->Parameter1;
			break;
		case MOD_ABSOLUTE:
			gold = fx->Parameter1-game->PartyGold;
			break;
		case MOD_PERCENT:
			gold = game->PartyGold*fx->Parameter1/100-game->PartyGold;
			break;
		default:
			//ie crashes here, i guess
			return FX_NOT_APPLIED;
	}
	game->AddGold (gold);
	return FX_NOT_APPLIED;
}

//0x6a
int fx_morale_break_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_morale_break_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD(IE_MORALEBREAK);
	return FX_PERMANENT; //permanent morale break doesn't stick
}

//0x6b
int fx_portrait_change (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_portrait_change (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	target->SetPortrait( fx->Resource, fx->Parameter2);
	return FX_NOT_APPLIED;
}

//0x6c
int fx_reputation_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_reputation_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD(IE_REPUTATION);
	return FX_NOT_APPLIED; //needs testing
}

//0x6d --> see later

//0x6e
//retreat_from (unknown)
//0x6f

EffectRef fx_remove_item_ref={"Item:Remove",NULL,-1};

int fx_create_magic_item (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	//charge count is incorrect
	target->inventory.SetSlotItemRes(fx->Resource, target->inventory.GetMagicSlot(),fx->Parameter1,fx->Parameter3,fx->Parameter4);
	if (fx->TimingMode==FX_DURATION_INSTANT_LIMITED) {
//if this effect has expiration, then it will remain as a remove_item
//on the effect queue, inheriting all the parameters
		fx->Opcode=EffectQueue::ResolveEffect(fx_remove_item_ref);
		fx->TimingMode=FX_DURATION_DELAY_PERMANENT;
		return FX_APPLIED;
	}
	return FX_NOT_APPLIED;
}

//0x70
int fx_remove_item (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	//will destroy the first item
	target->inventory.DestroyItem(fx->Resource,0,1);
	return FX_NOT_APPLIED;
}

//0x71
int fx_equip_item (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	target->inventory.EquipItem(fx->Parameter2, true);
	return FX_NOT_APPLIED;
}
//0x72
int fx_dither (Actor* /*Owner*/, Actor* /*target*/, Effect* /*fx*/)
{
	//dither (unknown)
	return FX_NOT_APPLIED;
}
//0x73 detect alignment
int fx_detect_alignment (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	ieDword msk = fx->Parameter2+1;
	if ( (target->GetStat(IE_ALIGNMENT)&AL_GNE_MASK) == msk) {
		//
	}
	return FX_NOT_APPLIED;
}
// 0x74
int fx_cure_improved_invisible_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_improved_invisible_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_CURE( STATE_INVISIBLE );
	STATE_CURE( STATE_INVIS2 );
	target->fxqueue.RemoveAllEffects(fx_set_invisible_state_ref);
	return FX_NOT_APPLIED;
}

// 0x75
int fx_reveal_area (Actor* /*Owner*/, Actor* target, Effect* /*fx*/)
{
	//reveals whole area
	target->GetCurrentArea()->Explore(-1);
	return FX_NOT_APPLIED;
}
// 0x76

// 0x77
EffectRef fx_mirror_image_modifier_ref={"MirrorImageModifier",NULL,-1};

int fx_mirror_image (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	fx->Opcode = EffectQueue::ResolveEffect(fx_mirror_image_modifier_ref);
	fx->Parameter1 = core->Roll(1, fx->Parameter1, 0);
	Effect *fx2 = target->fxqueue.HasEffect(fx_mirror_image_modifier_ref);
	if (fx2) {
		//update old effect with our numbers if our numbers are more
		if (fx2->Parameter1<fx->Parameter1) {
			fx2->Parameter1=fx->Parameter1;
		}
		if (fx->TimingMode==FX_DURATION_INSTANT_PERMANENT) {
			fx2->TimingMode = FX_DURATION_INSTANT_PERMANENT;
		}
		return FX_NOT_APPLIED;
	}
	return FX_APPLIED;
}
// 0x78
// 0x79
// 0x7a
EffectRef fx_remove_inventory_item_ref={"Item:RemoveInventory",NULL,-1};

int fx_create_inventory_item (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_create_inventory_item (%2d)\n", fx->Opcode );
	target->inventory.SetSlotItemRes( fx->Resource, -1, fx->Parameter1, fx->Parameter3, fx->Parameter4 );
        if (fx->TimingMode==FX_DURATION_INSTANT_LIMITED) {
//if this effect has expiration, then it will remain as a remove_item
//on the effect queue, inheriting all the parameters
                fx->Opcode=EffectQueue::ResolveEffect(fx_remove_inventory_item_ref);
                fx->TimingMode=FX_DURATION_DELAY_PERMANENT;
                return FX_APPLIED;
        }
	return FX_NOT_APPLIED;
}
// 0x7b
int fx_remove_inventory_item (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_remove_inventory_item (%2d)\n", fx->Opcode );
	target->inventory.DestroyItem(fx->Resource,IE_INV_ITEM_EQUIPPED,1);
	return FX_NOT_APPLIED;
}

// 0x7c
int fx_dimension_door (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_dimension_door (%2d)\n", fx->Opcode );
	Point p(fx->PosX, fx->PosY);
	target->SetPosition(target->GetCurrentArea(), p, true, 0 );
	return FX_NOT_APPLIED;
}
// 0x7d
int fx_knock (Actor* Owner, Actor* /*target*/, Effect* fx)
{
	if (0) printf( "fx_knock (%2d)\n", fx->Opcode );
	Map *map = Owner->GetCurrentArea();
	Point p(fx->PosX, fx->PosY);
	Door *door = map->TMap->GetDoor(p);
	if (door) {
		door->SetDoorLocked(false, true);
		return FX_NOT_APPLIED;
	}
	Container *container = map->TMap->GetContainer(p);
	if (container) {
		container->SetContainerLocked(false);
		return FX_NOT_APPLIED;
	}
	return FX_NOT_APPLIED;
}
// 0x7e
int fx_movement_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_slow_factor (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD(IE_MOVEMENTRATE);
	return FX_APPLIED;
}

// 0x7f
int fx_summon_monster (Actor* Owner, Actor* target, Effect* fx)
{
	if (0) printf( "fx_summon_monster (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	//check the summoning limit?

	ieResRef monster;

	//get monster resref from 2da determined by fx->Resource 
	DataStream* ds = core->GetResourceMgr()->GetResource( monster, IE_CRE_CLASS_ID );
	Actor *ab = core->GetCreature(ds);
	if (!ab) {
		return FX_NOT_APPLIED;
	}

	ab->LastSummoner = Owner->GetID();

	switch (fx->Parameter2) {
		case 0: case 1: case 3:
			ab->SetBase(IE_EA, EA_ALLY); //is this the summoned EA?
			break;
		case 5:
			ab->SetBase(IE_EA, EA_ENEMY);
			break;
		default:
			break;
	}

	//probably we should use the position in fx (and set it earlier)
	Point position = target->Pos;
	//
	//
	Map *map = target->GetCurrentArea();
	ab->SetPosition(map, position, true, 0);
	if (fx->Resource2[0]) {
		Point p(0,0);
		ScriptedAnimation* vvc = core->GetScriptedAnimation(fx->Resource2, p, 0);
		map->AddVVCCell( vvc );
	}

	return FX_APPLIED;
}

// 0x80
int fx_set_confused_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_confused_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_SET( STATE_CONFUSED );
	return FX_NOT_APPLIED;
}

// 0x81
int fx_set_aid_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_aid_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	if (!fx->Parameter2) {
		fx->Parameter2=core->Roll(fx->Parameter1,8,0);
	}
	if (STATE_GET (STATE_AID) ) //aid is non cummulative
		return FX_NOT_APPLIED;
	STATE_SET( STATE_AID );
	STAT_ADD( IE_MAXHITPOINTS, fx->Parameter2);
	STAT_ADD( IE_SAVEVSDEATH, fx->Parameter1);
	STAT_ADD( IE_SAVEVSWANDS, fx->Parameter1);
	STAT_ADD( IE_SAVEVSPOLY, fx->Parameter1);
	STAT_ADD( IE_SAVEVSBREATH, fx->Parameter1);
	STAT_ADD( IE_SAVEVSSPELL, fx->Parameter1);
	STAT_ADD( IE_HITBONUS, fx->Parameter1);
	return FX_APPLIED;
}

// 0x82
int fx_set_bless_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_bless_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	if (STATE_GET (STATE_BLESS) ) //bless is non cummulative
		return FX_NOT_APPLIED;
	STATE_SET( STATE_BLESS );
	STAT_ADD( IE_SAVEVSDEATH, fx->Parameter1);
	STAT_ADD( IE_SAVEVSWANDS, fx->Parameter1);
	STAT_ADD( IE_SAVEVSPOLY, fx->Parameter1);
	STAT_ADD( IE_SAVEVSBREATH, fx->Parameter1);
	STAT_ADD( IE_SAVEVSSPELL, fx->Parameter1);
	return FX_APPLIED;
}
// 0x83
int fx_set_chant_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_chant_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	if (STATE_GET (STATE_CHANT) ) //chant is non cummulative
		return FX_NOT_APPLIED;
	STATE_SET( STATE_CHANT );
	STAT_ADD( IE_SAVEVSDEATH, fx->Parameter1);
	STAT_ADD( IE_SAVEVSWANDS, fx->Parameter1);
	STAT_ADD( IE_SAVEVSPOLY, fx->Parameter1);
	STAT_ADD( IE_SAVEVSBREATH, fx->Parameter1);
	STAT_ADD( IE_SAVEVSSPELL, fx->Parameter1);
	return FX_APPLIED;
}

// 0x84
int fx_set_holy_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_holy_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	if (STATE_GET (STATE_HOLY) ) //holy power is non cummulative
		return FX_NOT_APPLIED;
	STATE_SET( STATE_HOLY );
	STAT_ADD( IE_STR, fx->Parameter1);
	STAT_ADD( IE_CON, fx->Parameter1);
	STAT_ADD( IE_DEX, fx->Parameter1);
	return FX_APPLIED;
}

// 0x85
int fx_set_luck (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_luck (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	if (STATE_GET (STATE_LUCK) ) //this luck is non cummulative
		return FX_NOT_APPLIED;
	if (0) printf( "fx_set_luck_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_SET( STATE_LUCK );
	STAT_SET( IE_LUCK, fx->Parameter1 );
	return FX_APPLIED;
}

// 0x86
int fx_set_petrified_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_petrified_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_SET( STATE_PETRIFIED );
	return FX_NOT_APPLIED;
}

// 0x87

// 0x88

// 0x89

// 0x8A

// 0x8B
// gemrb extension: rgb colour for displaystring
int fx_display_string (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_display_string (%2d): StrRef: %d\n", fx->Opcode, fx->Parameter1 );
	core->DisplayConstantStringName(fx->Parameter1, fx->Parameter2?fx->Parameter2:0xffffff, target);
	return FX_NOT_APPLIED;
}

//0x8f
int fx_create_item_in_slot (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_create_item_in_slot (%2d): Button: %d\n", fx->Opcode, fx->Parameter2 );
	//create item and set it in target's slot
	target->inventory.SetSlotItemRes( fx->Resource, core->QuerySlot(fx->Parameter2), fx->Parameter1, fx->Parameter3, fx->Parameter4 );
	if (fx->TimingMode!=FX_DURATION_INSTANT_LIMITED) {
		//convert it to a destroy item
		fx->Opcode=EffectQueue::ResolveEffect(fx_remove_item_ref);
		fx->TimingMode=FX_DURATION_DELAY_PERMANENT;
		return FX_APPLIED;
	}
	return FX_NOT_APPLIED;
}
// 0x90
int fx_disable_button (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	if (0) printf( "fx_disable_button (%2d): Button: %d\n", fx->Opcode, fx->Parameter2 );
	//
	return FX_APPLIED;
}

int fx_disable_spellcasting (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	if (0) printf( "fx_disable_spellcasting (%2d): Button: %d\n", fx->Opcode, fx->Parameter2 );
	//
	return FX_APPLIED;
}

// 0x93
int fx_learn_spell (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	//parameter1 is unused, gemrb lets you to make it not give XP
	//probably we should also let this via a game flag if we want 
	//full compatibility with bg1
	target->LearnSpell(fx->Resource, fx->Parameter1^LS_ADDXP);
	return FX_NOT_APPLIED;
}

// 0x98
int fx_play_movie (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	if (0) printf( "fx_play_movie (%2d): Resource: %s\n", fx->Opcode, fx->Resource );
	core->PlayMovie (fx->Resource);
	return FX_NOT_APPLIED;
}
// 0x99
int fx_set_sanctuary_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_sanctuary_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_SET( IE_SANCTUARY, 1);
	return FX_APPLIED; //is this correct?
}

// 0x9a
int fx_set_entangle_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_entangle_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_SET( IE_ENTANGLE, 1);
	return FX_APPLIED; //is this correct?
}

// 0x9b
int fx_set_minorglobe_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_minorglobe_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_SET( IE_MINORGLOBE, 1);
	return FX_APPLIED; //is this correct?
}

// 0x9c
int fx_set_shieldglobe_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_shieldglobe_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_SET( IE_SHIELDGLOBE, 1);
	return FX_APPLIED; //is this correct?
}

// 0x9d
int fx_set_web_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_web_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_SET( IE_WEB, 1);
	return FX_APPLIED; //is this correct?
}

// 0x9e
int fx_set_grease_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_grease_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_SET( IE_GREASE, 1);
	return FX_APPLIED; //is this correct?
}

// 0x9f
int fx_set_mirrorimages (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_mirrorimages (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_SET( IE_MIRRORIMAGES, fx->Parameter2);
	return FX_APPLIED;
}

// 0xa0
EffectRef fx_sanctuary_state_ref={"Overlay:Sanctuary",NULL,-1};

int fx_cure_sanctuary_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_sanctuary_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_SET( IE_SANCTUARY, 0);
	target->fxqueue.RemoveAllEffects(fx_sanctuary_state_ref);
	return FX_NOT_APPLIED;
}

// 0xa1
EffectRef fx_set_panic_state_ref={"State:Panic",NULL,-1};

int fx_cure_panic_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_panic_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_CURE( STATE_PANIC );
	target->fxqueue.RemoveAllEffects(fx_set_panic_state_ref);
	return FX_NOT_APPLIED;
}

// 0xa2
EffectRef fx_hold_creature_ref={"State:Hold",NULL,-1};

int fx_cure_hold_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_hold_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	//note that this effect doesn't remove 185 (another hold effect)
	target->fxqueue.RemoveAllEffects( fx_hold_creature_ref ); 
	return FX_NOT_APPLIED;
}

// 0xa3
EffectRef fx_movement_modifier_ref={"MovementModifier",NULL,-1};
// free action
int fx_free_action (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_free_action (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	target->fxqueue.RemoveAllEffects( fx_movement_modifier_ref ); 
//	STATE_CURE( STATE_SLOWED );
	return FX_NOT_APPLIED;
}

// 0xA4 //slow poison: generic effect

// 0xA5
int fx_pause_target (Actor* /*Owner*/, Actor *target, Effect* fx)
{
	if (0) printf( "fx_pause_target (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_CASTERHOLD );
	return FX_PERMANENT;
}

// 0xA6
int fx_magic_resistance_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_magic_resistance_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_RESISTMAGIC );
	return FX_APPLIED;
}

// 0xA7
int fx_missile_to_hit_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_missile_to_hit_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_MISSILEHITBONUS );
	return FX_APPLIED;
}

//0xae
int fx_playsound (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_playsound (%s)", fx->Resource );
	//this is probably inaccurate
	if (target) {
		core->GetSoundMgr()->Play(fx->Resource, target->Pos.x, target->Pos.y);
	} else {
		core->GetSoundMgr()->Play(fx->Resource);
	}
	return FX_APPLIED;
}

//0x6d
int fx_hold_creature_no_icon (Actor* /*Owner*/, Actor* target, Effect* fx)
{
 	if (match_ids( target, fx->Parameter1, fx->Parameter2) ) {
		STAT_SET( IE_HELD, 1);
		return FX_APPLIED;
	}
	//if the ids don't match, the effect doesn't stick
	return FX_NOT_APPLIED;
}

//0xaf, 0xb9
int fx_hold_creature (Actor* /*Owner*/, Actor* target, Effect* fx)
{
 	if (match_ids( target, fx->Parameter1, fx->Parameter2) ) {
		STAT_SET( IE_HELD, 1);
		return FX_APPLIED;
	}
	//if the ids don't match, the effect doesn't stick
	return FX_NOT_APPLIED;
}

// 0xBa
int fx_destroy_self (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_destroy_self (%2d)", fx->Opcode );
	target->DestroySelf();
	return FX_APPLIED;
}

// 0xBB
int fx_local_variable (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	//this is a hack, the variable name spreads across the resources
	if (0) printf( "fx_local_variable (%2d) %s=%d", fx->Opcode, fx->Resource, fx->Parameter1 );
	target->locals->SetAt(fx->Resource, fx->Parameter1);
	//local variable effects are not applied, they will be resaved though
	return FX_NOT_APPLIED;
}

// 0xbf
int fx_spell_casting_level_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_spell_level_modifier (%2d) Value:%d Type:%d", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	switch (fx->Parameter2) {
	case 0:
		STAT_SET( IE_CASTINGLEVELBONUSMAGE, fx->Parameter1 );
		break;
	case 1:
		STAT_SET( IE_CASTINGLEVELBONUSCLERIC, fx->Parameter1 );
		break;
	}
	return FX_APPLIED;
}

// 0xc1
int fx_see_invisible_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_see_invisible_modifier (%2d): Type: %d\n", fx->Opcode, fx->Parameter2 );
	STAT_SET( IE_SEEINVISIBLE, fx->Parameter2 );
	return FX_APPLIED;
}

// 0xc2
int fx_ignore_dialogpause_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_ignore_dialogpause_modifier (%2d): Type: %d\n", fx->Opcode, fx->Parameter2 );
	STAT_SET( IE_IGNOREDIALOGPAUSE, fx->Parameter2 );
	return FX_APPLIED;
}

// 0xc5
int fx_bounce_projectile (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_bounce_projectile (%2d): Type: %d\n", fx->Opcode, fx->Parameter2 );
	STAT_SET( IE_BOUNCE, 1 );
	return FX_APPLIED;
}

// 0xd0
int fx_minimum_hp_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_minimum_hp_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_MINHITPOINTS );
	return FX_APPLIED;
}

//0xd1
int fx_power_word_kill (Actor* Owner, Actor* target, Effect* fx)
{
	ieDword limit = 60;

	if (fx->Parameter1) {
		limit = fx->Parameter1;
	}
	//normally this would work only with hitpoints
	//but why not add some extra features
	if (target->GetStat (fx->Parameter2) < limit) {
		target->Die( Owner );
	}
	return FX_NOT_APPLIED;
}

// 0xd7
int fx_play_visual_effect (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_play_visual_effect (%2d): Resource: %s\n", fx->Opcode, fx->Resource );
	if (fx->Resource[0]) {
		Point p(0,0);
		ScriptedAnimation* vvc = core->GetScriptedAnimation(fx->Resource, p, 0);
		target->GetCurrentArea( )->AddVVCCell( vvc );
	}
	return FX_APPLIED;
}

// 0xDA
int fx_stoneskin_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_stoneskin_modifier (%2d): Mod: %d\n", fx->Opcode, fx->Parameter2 );
	STAT_SET(IE_STONESKINS, fx->Parameter1);
	return FX_APPLIED;
}

// 0xE9
int fx_proficiency (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_proficiency (%2d): Value: %d, Stat: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	//probably no need to check the boundaries, the original IE
	//did check it (though without boundaries, it is more useful)
	STAT_SET (fx->Parameter2, fx->Parameter1);
	return FX_APPLIED;
}

// 0xea
int fx_create_contingency (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	if (0) printf( "fx_create_contingency (%2d): Value: %d, Stat: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	return FX_NOT_APPLIED;
}

#define WB_AWAY 0
#define WB_TOWARDS 1
#define WB_FIXDIR 2
#define WB_OWNDIR 3
#define WB_AWAYOWNDIR 4

// 0xeb
int fx_wing_buffet (Actor* Owner, Actor* target, Effect* fx)
{
	if (0) printf( "fx_wing_buffet (%2d): Value: %d, Stat: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	//create movement in actor

	ieDword dir;
	switch(fx->Parameter2) {
		case WB_AWAY:
		default:
			dir = GetOrient(Owner->Pos, target->Pos);
			break;
		case WB_TOWARDS:
			dir = GetOrient(target->Pos, Owner->Pos);
			break;
		case WB_FIXDIR:
			dir = fx->Parameter3;
			break;
		case WB_OWNDIR:
			dir = target->GetOrientation();
			break;
		case WB_AWAYOWNDIR:
			dir = target->GetOrientation()^8;
			break;
	}
	//could be GL_REBOUND too :)
	//add effect to alter target's stance
	target->MoveLine( fx->Parameter1, GL_NORMAL, dir );
	return FX_APPLIED;
}

// 0xec
int fx_puppet_master (Actor* /*Owner*/, Actor* target, Effect* fx)
{
        if (0) printf( "fx_puppet_master (%2d): Value: %d, Stat: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_SET (IE_PUPPETMASTERTYPE, fx->Parameter1);
	return FX_APPLIED;
}
// 0xed
int fx_puppet (Actor* /*Owner*/, Actor* target, Effect* fx)
{
        if (0) printf( "fx_puppet (%2d): Value: %d, Stat: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_SET (IE_PUPPETTYPE, fx->Parameter1);
	return FX_APPLIED;
}

// 0xee
int fx_disintegrate (Actor* Owner, Actor* target, Effect* fx)
{
	if (0) printf( "fx_disintegrate (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
 	if (match_ids( target, fx->Parameter1, fx->Parameter2) ) {
		target->Damage(0, fx->Parameter2, Owner); //hmm?
		//death has damage type too
		target->Die(Owner);
	}
	return FX_NOT_APPLIED;
}
// 0xef
int fx_farsee (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	if (0) printf( "fx_farsee (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	//invoke farsee guiscript
	return FX_NOT_APPLIED;
}

// 0xf0
EffectRef fx_display_portrait_icon_ref={"Icon:Display",NULL,-1};

int fx_remove_portrait_icon (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_remove_portrait_icon (%2d): Type: %d\n", fx->Opcode, fx->Parameter2 );
	target->fxqueue.RemoveAllEffectsWithParam( fx_display_portrait_icon_ref, fx->Parameter2 );
	return FX_NOT_APPLIED;
}
// 0xf1

// 0xF2
int fx_cure_confused_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_cure_confused_state (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STATE_CURE( STATE_CONFUSED );
	return FX_NOT_APPLIED;
}
// 0xff
int fx_create_item_days (Actor* /*Owner*/, Actor* target, Effect* fx)
{
        if (0) printf( "fx_create_inventory_item (%2d)\n", fx->Opcode );
        target->inventory.SetSlotItemRes( fx->Resource, -1, fx->Parameter1, fx->Parameter3, fx->Parameter4 );
        if (fx->TimingMode==FX_DURATION_INSTANT_LIMITED) {
//if this effect has expiration, then it will remain as a remove_item
//on the effect queue, inheriting all the parameters
		//duration needs a hack (recalculate it for days)
		//no idea if this multiplier is ok
		fx->Duration+=(fx->Duration-core->GetGame()->GameTime)*2400;
                fx->Opcode=EffectQueue::ResolveEffect(fx_remove_inventory_item_ref
);
                fx->TimingMode=FX_DURATION_DELAY_PERMANENT;
                return FX_APPLIED;
        }
        return FX_NOT_APPLIED;
}
// 0x100
int fx_store_spell_sequencer(Actor* /*Owner*/, Actor* /*target*/, Effect* /*fx*/)
{
	//just display the spell sequencer portrait icon
	return FX_APPLIED;
}
// 0x101
int fx_create_spell_sequencer(Actor* /*Owner*/, Actor* /*target*/, Effect* /*fx*/)
{
	//just a call to activate the spell sequencer creation gui
	return FX_NOT_APPLIED;
}

// 0x102
EffectRef fx_spell_sequencer_active_ref={"Sequencer:Store",NULL,-1};

int fx_activate_spell_sequencer(Actor* Owner, Actor* target, Effect* fx)
{
	Effect *sequencer = Owner->fxqueue.HasEffect(fx_spell_sequencer_active_ref);
	core->ApplySpell(sequencer->Resource, Owner, target, fx->Power);
	core->ApplySpell(sequencer->Resource2, Owner, target, fx->Power);
	core->ApplySpell(sequencer->Resource3, Owner, target, fx->Power);
	//remove the spell sequencer store
	//cast 1-3 spells stored in the spell sequencer
	return FX_NOT_APPLIED;
}
// 0x103
int fx_spelltrap(Actor* /*Owner*/, Actor* /*target*/, Effect* /*fx*/)
{
	//it has some portrait icon i think
	return FX_APPLIED;
}
// 0x104 //crashes
// 0x105
int fx_restore_spell_level(Actor* /*Owner*/, Actor* target, Effect* fx)
{
	target->RestoreSpellLevel(fx->Parameter1, fx->Parameter2);
	return FX_NOT_APPLIED;
}
// 0x106
int fx_visual_range_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_visual_range_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD( IE_VISUALRANGE );
	return FX_APPLIED;
}

// 0x107
int fx_backstab_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_visual_range_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD( IE_BACKSTABDAMAGEMULTIPLIER );
	return FX_APPLIED;
}

// 0x108
int fx_drop_weapon (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (fx->Resource[0]) {
		target->DropItem(fx->Resource, 0);
		return FX_NOT_APPLIED;
	}
	switch (fx->Parameter2) {
		case 0:
			target->DropItem(-1, 0);
			break;
		case 1:
			target->DropItem(target->inventory.GetEquippedSlot(), 0);
			break;
		default:
			target->DropItem(fx->Parameter1, 0);
			break;
	}
	return FX_NOT_APPLIED;
}
// 0x109
int fx_modify_global_variable (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	Game *game = core->GetGame();
	//convert it to internal variable format
	if (!fx->IsVariable) {
		memmove(fx->Resource+8, fx->Resource2,8);
		memmove(fx->Resource+16, fx->Resource3,8);
		memmove(fx->Resource+24, fx->Resource4,8);
		fx->IsVariable=1;
	}
	if (0) printf( "fx_modify_local_variable (%2d): Variable: %s Value: %d Type: %d\n", fx->Opcode, fx->Resource, fx->Parameter1, fx->Parameter2 );
	if (fx->Parameter2) {
		ieDword var = 0;
		//use resource memory area as variable name
		game->locals->Lookup(fx->Resource, var);
		game->locals->SetAt(fx->Resource, var+fx->Parameter1);
	} else {
		game->locals->SetAt(fx->Resource, fx->Parameter1);
	}
	return FX_NOT_APPLIED;
}
// 0x10a unknown
// 0x10b protection from display string is a generic effect
// 0x10c
int fx_explore_modifier (Actor* /*Owner*/, Actor* target, Effect* /*fx*/)
{
	STAT_SET (IE_EXPLORE, 1);
	return FX_APPLIED;
}
// 0x10d
int fx_screenshake (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	core->timer->SetScreenShake( fx->Parameter1, fx->Parameter1, 1);
	return FX_APPLIED;
}

// 0x10e
EffectRef fx_pause_caster_modifier_ref={"PauseTarget",NULL,-1};

int fx_unpause_caster (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_unpause_caster (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	Effect *eff = target->fxqueue.HasEffect(fx_pause_caster_modifier_ref);
	if (eff) {
		eff->Parameter1-=fx->Parameter2;
	}
	return FX_NOT_APPLIED;
}
// 0x10f
int fx_avatar_removal (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	if (0) printf( "fx_avatar_removal (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	return FX_APPLIED;
}
// 0x110
int fx_apply_spell_on_condition (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	if (0) printf( "fx_apply_spell_on_condition (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	return FX_APPLIED;
}
// 0x111
int fx_remove_area_effect (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	//instant effect
	if (0) printf( "fx_remove_area_effect (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	return FX_NOT_APPLIED;
}

// 0x112
int fx_teleport_to_target (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_teleport_to_target (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	Map *map = target->GetCurrentArea();
	if (map) {
		Actor *victim = map->GetActorByGlobalID(target->LastAttacker);
		if (victim) {
			target->SetPosition( map, victim->Pos, true, 0 );
		}
	}
	return FX_APPLIED;
}
// 0x113
int fx_hide_in_shadows_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_hide_in_shadows_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD( IE_HIDEINSHADOWS );
	return FX_APPLIED;
}
// 0x114
int fx_detect_illusion_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_detect_illusion_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD( IE_DETECTILLUSIONS );
	return FX_APPLIED;
}
// 0x115
int fx_set_traps_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_set_traps_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD( IE_SETTRAPS );
	return FX_APPLIED;
}
// 0x116
int fx_to_hit_bonus_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_to_hit_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD( IE_HITBONUS );
	return FX_APPLIED;
}

// 0x117
EffectRef fx_disable_button_ref={"DisableButton",NULL,-1};

int fx_renable_button (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	//removes the disable button effect
	if (0) printf( "fx_renable_button (%2d): Type: %d\n", fx->Opcode, fx->Parameter2 );
	target->fxqueue.RemoveAllEffectsWithParam( fx_disable_button_ref, fx->Parameter2 );
	return FX_NOT_APPLIED;
}
// 0x118
int fx_force_surge_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_force_surge_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD( IE_FORCESURGE );
	return FX_APPLIED;
}

// 0x119
int fx_wild_surge_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_wild_surge_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD( IE_SURGEMOD );
	return FX_APPLIED;
}
// 0x11a
int fx_scripting_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_scripting_state (%2d): Value: %d, Stat: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	//original engine didn't check boundaries, causing crashes
	//we allow only positive indices
	if (fx->Parameter2>100) {
		return FX_NOT_APPLIED;
	}
	STAT_SET( IE_SCRIPTINGSTATE1+fx->Parameter2, fx->Parameter1 );
	return FX_APPLIED;
}
// 0x11b
int fx_apply_effect (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_apply_effect (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	if (match_ids( target, fx->Parameter1, fx->Parameter2) ) {
		//load effect and add it to the end of the effect queue?
	}
	return FX_APPLIED;
}

// 0x11c
int fx_melee_to_hit_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_melee_to_hit_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD( IE_MELEEHIT );
	return FX_APPLIED;
}

// 0x11d
int fx_melee_damage_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_melee_damage_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD( IE_MELEEDAMAGE );
	return FX_APPLIED;
}

// 0x11e
int fx_missile_damage_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_missile_damage_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD( IE_MISSILEDAMAGE );
	return FX_APPLIED;
}

// 0x11f
int fx_no_circle_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_missile_damage_modifier (%2d)\n", fx->Opcode);
	STAT_SET( IE_NOCIRCLE, 1 );
	return FX_APPLIED;
}

// 0x120
int fx_fist_to_hit_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_fist_to_hit_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD( IE_FISTHIT );
	return FX_APPLIED;
}

// 0x121
int fx_fist_damage_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_fist_damage_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_MOD( IE_FISTDAMAGE );
	return FX_APPLIED;
}
//0x122
int fx_title_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_fist_damage_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	if (fx->Parameter2) {
		STAT_SET( IE_TITLE2, fx->Parameter1 );
	} else {
		STAT_SET( IE_TITLE1, fx->Parameter1 );
	}
	return FX_APPLIED;
}
//0x123
int fx_disable_overlay_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_disable_overlay_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_SET( IE_DISABLEOVERLAY, fx->Parameter1 );
	return FX_APPLIED;
}
//0x124
int fx_disable_backstab_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_disable_backstab_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_SET( IE_DISABLEBACKSTAB, fx->Parameter1 );
	return FX_APPLIED;
}
//0x125
int fx_offscreenai_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_offscreenai_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_SET( IE_ENABLEOFFSCREENAI, fx->Parameter1 );
	return FX_APPLIED;
}
//0x126
int fx_soundmn_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_soundmn_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_SET( IE_SOUNDMN, fx->Parameter1 );
	return FX_APPLIED;
}
//0x127
int fx_disable_chunk_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_disable_chunk_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	STAT_SET( IE_DISABLECHUNKING, fx->Parameter1 );
	return FX_APPLIED;
}
//0x128
int fx_protection_from_animation (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_protection_from_animation (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	//remove vvc from actor if active
	target->RemoveVVCell(fx->Resource, false);
	return FX_APPLIED;
}
//0x129
int fx_non_interruptible_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_non_interruptible_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	//remove vvc from actor if active
	STAT_SET( IE_NONINTERRUPTABLE, fx->Parameter1 );
	return FX_APPLIED;
}
//0x12a weird effect (pocket plane)
int fx_area_switch (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	//unknown
	//makes cutscenemode
	if (0) printf( "fx_area_switch (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	return FX_NOT_APPLIED;
}
//0x12b
int fx_chaos_shield_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_chaos_shield_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	//remove vvc from actor if active
	STAT_MOD( IE_CHAOSSHIELD );
	return FX_APPLIED;
}
//0x12c
int fx_deactivate_dead_modifier (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	//unknown
	if (0) printf( "fx_deactivate_dead_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	return FX_APPLIED;
}
//0x12d
int fx_critical_hit_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_critical_hit_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );
	//remove vvc from actor if active
	STAT_MOD( IE_CRITICALHITBONUS );
	return FX_APPLIED;
}
// 0x12e
int fx_can_use_any_item_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_can_use_any_item_modifier (%2d): Value: %d\n", fx->Opcode, fx->Parameter2 );

	STAT_SET( IE_CANUSEANYITEM, fx->Parameter2 );
	return FX_APPLIED;
}

// 0x12f
int fx_always_backstab_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_always_backstab_modifier (%2d): Value: %d\n", fx->Opcode, fx->Parameter2 );

	STAT_SET( IE_ALWAYSBACKSTAB, fx->Parameter2 );
	return FX_APPLIED;
}

// 0x130
int fx_mass_raise_dead (Actor* /*Owner*/, Actor* /*target*/, Effect* /*fx*/)
{
	//raise dead all partymember?
	return FX_NOT_APPLIED;
}

// 0x131
int fx_left_to_hit_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_to_hit_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_HITBONUSLEFT );
	return FX_APPLIED;
}

// 0x132
// 0x133
int fx_reveal_tracks (Actor* /*Owner*/, Actor* /*target*/, Effect* fx)
{
	if (0) printf( "fx_reveal_tracks (%2d): Distance: %d\n", fx->Opcode, fx->Parameter1 );
	//write tracks.2da entry
	//highlight all creatures
	return FX_NOT_APPLIED; //this is an instant effect
}
// 0x134
int fx_stat195_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_stat195_modifier (%2d): Mod: %d, Type: %d\n", fx->Opcode, fx->Parameter1, fx->Parameter2 );

	STAT_MOD( IE_EFFECT308 ); //highlight creature???
	return FX_APPLIED;
}
// 0x135
int fx_modify_local_variable (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	//convert it to internal variable format
	if (!fx->IsVariable) {
		memmove(fx->Resource+8, fx->Resource2,8);
		memmove(fx->Resource+16, fx->Resource3,8);
		memmove(fx->Resource+24, fx->Resource4,8);
		fx->IsVariable=1;
	}
	if (0) printf( "fx_modify_local_variable (%2d): %s, Mod: %d\n", fx->Opcode, fx->Resource, fx->Parameter2 );
	if (fx->Parameter2) {
		ieDword var = 0;
		//use resource memory area as variable name
		target->locals->Lookup(fx->Resource, var);
		target->locals->SetAt(fx->Resource, var+fx->Parameter1);
	} else {
		target->locals->SetAt(fx->Resource, fx->Parameter1);
	}
	return FX_NOT_APPLIED;
}

// 0x136
int fx_timeless_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_to_hit_modifier (%2d): Mod: %d\n", fx->Opcode, fx->Parameter2 );
	STAT_SET(IE_DISABLETIMESTOP, fx->Parameter2);
	return FX_APPLIED;
}

//0x137
//0x138
//0x139
//0x13a
int fx_golem_stoneskin_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_golem_stoneskin_modifier (%2d): Mod: %d\n", fx->Opcode, fx->Parameter2 );
	STAT_SET(IE_STONESKINSGOLEM, fx->Parameter1);
	return FX_APPLIED;
}

// 0x13b
int fx_avatar_removal_modifier (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_avatar_removal_modifier (%2d): Mod: %d\n", fx->Opcode, fx->Parameter2 );
	STAT_SET(IE_AVATARREMOVAL, fx->Parameter2);
	return FX_APPLIED;
}
// 0x13c
int fx_magical_rest (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_magical_rest (%2d)\n", fx->Opcode );
	target->Rest(0);       //full rest
	return FX_NOT_APPLIED; //this is an instant effect
}

// 0x13d
int fx_improved_haste_state (Actor* /*Owner*/, Actor* target, Effect* fx)
{
	if (0) printf( "fx_improved_haste_state (%2d): Value: %d\n", fx->Opcode, fx->Parameter2 );
	STAT_SET(IE_IMPROVEDHASTE, fx->Parameter2);
	return FX_APPLIED;
}
