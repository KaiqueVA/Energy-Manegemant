import { ComponentFixture, TestBed } from '@angular/core/testing';

import { SwitchTomadaComponent } from './switch-tomada.component';

describe('SwitchTomadaComponent', () => {
  let component: SwitchTomadaComponent;
  let fixture: ComponentFixture<SwitchTomadaComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [SwitchTomadaComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(SwitchTomadaComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
