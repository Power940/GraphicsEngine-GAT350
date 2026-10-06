#include "pch.h"
#include "ParticleSystem.h"


namespace STR_FALL
{
	bool ParticleSystem2D::Initialize(size_t size)
	{
		m_particles.resize(size);
		return true;
	}

	void ParticleSystem2D::Shutdown() { m_particles.clear(); }
	
	void ParticleSystem2D::Update(float dt)
	{
		for (Particle2D& particle : m_particles)
		{
			if (!particle.m_active) { continue; }
			particle.m_lifespan -= dt;
			particle.m_active = particle.m_lifespan > 0;
			particle.m_position += particle.m_velocity * dt;
		}
	}

	void ParticleSystem2D::Draw(Renderer& r)
	{
		for (Particle2D& particle : m_particles)
		{
			if (particle.m_active)
			{
				r.RenderTexture(particle.m_texture.get(), particle.m_position.m_x, particle.m_position.m_y);
			}
		}
	}

	void ParticleSystem2D::AddParticle(const Particle2D& particle)
	{
		Particle2D* freeParticle = GetFreeParticle();
		if (freeParticle)
		{
			*freeParticle = particle;
			freeParticle->m_active = true;
		}
	}

	Particle2D* ParticleSystem2D::GetFreeParticle()
	{
		for (Particle2D& particle : m_particles)
		{
			if (!particle.m_active) { return &particle; }
		}
		return nullptr;
	}
}