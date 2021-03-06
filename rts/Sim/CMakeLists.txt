
# This list was created using this *nix shell command:
# > find . -name "*.cpp"" | sort
SET(sources_engine_Sim
		"${CMAKE_CURRENT_SOURCE_DIR}/Features/Feature.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Features/FeatureDef.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Features/FeatureHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/AirBaseHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/AllyTeam.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/CategoryHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/CollisionHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/CollisionVolume.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/CommonDefHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/DamageArray.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/DamageArrayHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/GeometricObjects.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/GlobalSynced.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/GroundBlockingObjectMap.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/InterceptHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/LosHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/LosMap.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/ModInfo.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/QuadField.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/RadarHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Resource.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/ResourceHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/ResourceMapAnalyzer.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/SideParser.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/SmoothHeightMesh.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Team.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/TeamBase.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/TeamHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/TeamStatistics.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Misc/Wind.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MoveTypes/AAirMoveType.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MoveTypes/AirMoveType.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MoveTypes/GroundMoveType.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MoveTypes/MoveInfo.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MoveTypes/MoveMath/GroundMoveMath.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MoveTypes/MoveMath/HoverMoveMath.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MoveTypes/MoveMath/MoveMath.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MoveTypes/MoveMath/ShipMoveMath.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MoveTypes/MoveType.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MoveTypes/MoveTypeFactory.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MoveTypes/ScriptMoveType.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MoveTypes/StaticMoveType.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/MoveTypes/TAAirMoveType.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Objects/SolidObject.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Objects/WorldObject.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Path/Default/PathAllocator.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Path/Default/PathCache.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Path/Default/PathEstimator.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Path/Default/PathFinder.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Path/Default/PathFinderDef.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Path/Default/PathManager.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Path/IPathManager.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/ExpGenSpawner.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/ExplosionListener.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/ExplosionGenerator.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/FireProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/FlareProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/PieceProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Projectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/ProjectileHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/BitmapMuzzleFlame.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/BubbleProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/DirtProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/ExploSpikeProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/FlyingPiece.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/GenericParticleProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/GeoSquareProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/GeoThermSmokeProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/GfxProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/HeatCloudProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/MuzzleFlame.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/RepulseGfx.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/ShieldPartProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/SimpleParticleSystem.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/SmokeProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/SmokeProjectile2.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/SmokeTrailProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/SpherePartProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/TracerProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/WakeProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/Unsynced/WreckProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/WeaponProjectiles/BeamLaserProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/WeaponProjectiles/EmgProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/WeaponProjectiles/ExplosiveProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/WeaponProjectiles/FireBallProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/WeaponProjectiles/FlameProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/WeaponProjectiles/LargeBeamLaserProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/WeaponProjectiles/LaserProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/WeaponProjectiles/LightningProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/WeaponProjectiles/MissileProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/WeaponProjectiles/StarburstProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/WeaponProjectiles/TorpedoProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/WeaponProjectiles/WeaponProjectile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/BuildInfo.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/CommandAI/AirCAI.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/CommandAI/BuilderCAI.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/CommandAI/Command.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/CommandAI/CommandAI.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/CommandAI/FactoryCAI.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/CommandAI/MobileCAI.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/CommandAI/TransportCAI.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/Groups/Group.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/Groups/GroupHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/Scripts/CobEngine.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/Scripts/CobFile.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/Scripts/CobInstance.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/Scripts/CobScriptNames.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/Scripts/CobThread.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/Scripts/LuaScriptNames.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/Scripts/LuaUnitScript.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/Scripts/NullUnitScript.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/Scripts/UnitScript.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/Scripts/UnitScriptEngine.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/Scripts/UnitScriptFactory.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/Unit.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/UnitDef.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/UnitDefHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/UnitHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/UnitLoader.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/UnitSet.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/UnitTypes/Builder.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/UnitTypes/Building.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/UnitTypes/ExtractorBuilding.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/UnitTypes/Factory.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Units/UnitTypes/TransportUnit.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/BeamLaser.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/Cannon.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/DGunWeapon.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/EmgCannon.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/FlameThrower.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/LaserCannon.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/LightningCannon.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/MeleeWeapon.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/MissileLauncher.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/NoWeapon.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/PlasmaRepulser.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/Rifle.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/StarburstLauncher.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/TorpedoLauncher.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/Weapon.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/WeaponDef.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/WeaponDefHandler.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/Weapons/bombdropper.cpp"
	)

MakeGlobal(sources_engine_Sim)
